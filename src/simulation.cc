#include "common/common.hh"
#include "indicators.hh"
#include "testfunc.hh"

#include "random/random_search.hh"
#include "gsa/gsa.hh"

#include <sys/stat.h>
#include <sys/types.h>

#include <Eigen/Core>

#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

namespace simulation {  
  std::string const OUTPUT_ROOT = "output/simulation/";
  
  template<typename Technique>
  void run_simulation(Technique   const &tech,
                      std::string const &tag_func,
                      std::string const &tag_verf,
                      std::size_t simcount)
  {
    gsa::displacements = 0;
    std::vector<std::unique_ptr<typename Technique::stepper>> steppers;

    for(std::size_t i = 0; i < simcount; ++i) {
      steppers.push_back(tech.create_stepper());
    }

    std::string output_path = OUTPUT_ROOT + tag_func;
    mkdir(output_path.c_str(), 0755);
    
    std::ofstream out_stat(output_path + "/" + tag_verf + ".tsv");

    out_stat << "step\tavg_best\tmed_best\tbest\tworst\n";

    std::cout << tag_func << "_" << tag_verf << ": " << std::string(20 - tag_verf.size(), ' ') << std::flush;
    std::clock_t start = std::clock();

    for(std::size_t step = 1; step <= tech.max_steps(); ++step) {
      // #pragma omp parallel for
      for(std::size_t i = 0; i < steppers.size(); ++i) {
        steppers[i]->step();
      }

      indicators ind(steppers);

      out_stat << step
               << "\t" << std::setprecision(16) << std::scientific << ind.avg()
               << "\t" << std::setprecision(16) << std::scientific << ind.median()
               << "\t" << std::setprecision(16) << std::scientific << ind.best()
               << "\t" << std::setprecision(16) << std::scientific << ind.worst()
               << std::endl;
    }

    std::clock_t end = std::clock();

    indicators ind(steppers);
    std::cout << std::fixed << double(end - start) / CLOCKS_PER_SEC / steppers.size() << " Sekunden"
	      << ", Avg: "    << std::setprecision(8) << std::scientific << ind.avg   ()
              << ", Median: " << std::setprecision(8) << std::scientific << ind.median()
              << ", Best: "   << std::setprecision(8) << std::scientific << ind.best  ()
	      << ", Worst: "  << std::setprecision(8) << std::scientific << ind.worst ();

    if(tag_func.substr(0, 6) == "sphere") {
      std::cout << ", d: " << std::setprecision(8) << std::scientific << std::sqrt(ind.median());
      //	      << ", d:" << std::setprecision(16) << (steppers[simcount / 2]->global_best().position() - Eigen::MatrixXd::Identity(tech.param().dimensions(), tech.param().dimensions()).diagonal()).norm()
    }
    std::cout << ", oob: " << double(gsa::displacements) / simcount
              << "\n";

    // auto dumpsolution = [&](std::size_t pos) {
    // 			  std::ostringstream title;
    // 			  title << output_path << "/" << tag_verf << ".solution." << pos << ".txt";
    // 			  std::ofstream out_sol(title.str().c_str());

    // 			  out_sol << std::setprecision(16) << steppers[pos]->global_best().position() << std::endl;
    // 			};

    // for(std::size_t i = 0; i < steppers.size(); ++i) {
    //   dumpsolution(i);
    // }

    std::ofstream out_hist(output_path + "/" + tag_verf + ".histogram.txt");
    for(auto &s : steppers) {
      out_hist << std::setprecision(16) << s->global_best().fitness() << "\n";
    }
  }
}

enum {
      RANDOM_SEARCH          = 1 << 0,
      GSA                    = 1 << 1,
};

int main() {
  std::uint32_t enabled_tests = 0
    | RANDOM_SEARCH     
    | GSA                   
    ;  

  std::size_t const max_steps = 1000;
  std::size_t const popsize   =   50;
  
  struct testcase {
    common::function_type func;
    std::string tag;
    common::limits limit_pos;
    common::index_type dimensionality;

    double G0;
    double alpha;

    std::size_t simcount;
  } testfuncs[] = {
#define TC_SPHERE(dim, G0, alpha)     { gsapaper_f1, "sphere_"     #dim "_" #alpha, { -100    , 100     }, dim, G0, alpha,  101 }
#define TC_ROSENBROCK(dim, G0, alpha) { rosenbrock , "rosenbrock_" #dim "_" #G0   , { -  2.048,   2.048 }, dim, G0, alpha, 1001 }
#define TC_RASTRIGIN(dim, G0, alpha)  { rastrigin  , "rastrigin_"  #dim "_" #G0   , { -  5.12 ,   5.12  }, dim, G0, alpha, 1001 }

    TC_SPHERE(2, 400,  2), TC_SPHERE(10, 400,  2), TC_SPHERE(30, 400,  2), TC_SPHERE(50, 400,  2), TC_SPHERE(100, 400,  2),
    TC_SPHERE(2, 400,  5), TC_SPHERE(10, 400,  5), TC_SPHERE(30, 400,  5), TC_SPHERE(50, 400,  5), TC_SPHERE(100, 400,  5),
    TC_SPHERE(2, 400, 10), TC_SPHERE(10, 400, 10), TC_SPHERE(30, 400, 10), TC_SPHERE(50, 400, 10), TC_SPHERE(100, 400, 10),
    TC_SPHERE(2, 400, 20), TC_SPHERE(10, 400, 20), TC_SPHERE(30, 400, 20), TC_SPHERE(50, 400, 20), TC_SPHERE(100, 400, 20),
    TC_SPHERE(2, 400, 30), TC_SPHERE(10, 400, 30), TC_SPHERE(30, 400, 30), TC_SPHERE(50, 400, 30), TC_SPHERE(100, 400, 30),
    TC_SPHERE(2, 400, 50), TC_SPHERE(10, 400, 50), TC_SPHERE(30, 400, 50), TC_SPHERE(50, 400, 50), TC_SPHERE(100, 400, 50),
    TC_SPHERE(2, 400, 80), TC_SPHERE(10, 400, 80), TC_SPHERE(30, 400, 80), TC_SPHERE(50, 400, 80), TC_SPHERE(100, 400, 80),
    
    TC_ROSENBROCK(2 ,    1   , 18.420680743952367),
    TC_ROSENBROCK(2 ,    2   , 19.11382792451231 ),
    TC_ROSENBROCK(2 ,    4   , 19.806975105072254),
    TC_ROSENBROCK(2 ,    7.09, 20.379366084498542),
    TC_ROSENBROCK(2 ,    8   , 20.5001222856322  ),
    TC_ROSENBROCK(2 ,   11.58, 20.869960216097216),
    TC_ROSENBROCK(2 ,   16   , 21.193269466192145),
    TC_ROSENBROCK(2 ,   32   , 21.886416646752092),
    TC_ROSENBROCK(2 ,   64   , 22.579563827312036),
    TC_ROSENBROCK(2 ,  128   , 23.272711007871983),
    TC_ROSENBROCK(2 ,  256   , 23.965858188431927),
    TC_ROSENBROCK(2 ,  512   , 24.659005368991874),
    TC_ROSENBROCK(2 , 1024   , 25.352152549551818),
    TC_ROSENBROCK(2 , 2048   , 26.045299730111765),
    TC_ROSENBROCK(2 , 4096   , 26.73844691067171 ),

    TC_ROSENBROCK(7 ,    1   , 18.420680743952367),
    TC_ROSENBROCK(7 ,    2   , 19.11382792451231 ),
    TC_ROSENBROCK(7 ,    4   , 19.806975105072254),
    TC_ROSENBROCK(7 ,    7.09, 20.379366084498542),
    TC_ROSENBROCK(7 ,    8   , 20.5001222856322  ),
    TC_ROSENBROCK(7 ,   16   , 21.193269466192145),
    TC_ROSENBROCK(7 ,   21.67, 21.496609559500634),
    TC_ROSENBROCK(7 ,   32   , 21.886416646752092),
    TC_ROSENBROCK(7 ,   64   , 22.579563827312036),
    TC_ROSENBROCK(7 ,  128   , 23.272711007871983),
    TC_ROSENBROCK(7 ,  256   , 23.965858188431927),
    TC_ROSENBROCK(7 ,  512   , 24.659005368991874),
    TC_ROSENBROCK(7 , 1024   , 25.352152549551818),
    TC_ROSENBROCK(7 , 2048   , 26.045299730111765),
    TC_ROSENBROCK(7 , 4096   , 26.73844691067171 ),

    TC_RASTRIGIN(30,     1     , 6.907755278982137 ),
    TC_RASTRIGIN(30,     2     , 7.600902459542082 ),
    TC_RASTRIGIN(30,     4     , 8.294049640102028 ),
    TC_RASTRIGIN(30,     8     , 8.987196820661973 ),
    TC_RASTRIGIN(30,    13.302 , 9.495669678844367 ),
    TC_RASTRIGIN(30,    16     , 9.680344001221918 ),
    TC_RASTRIGIN(30,    32     , 10.373491181781864),
    TC_RASTRIGIN(30,    64     , 11.06663836234181 ),
    TC_RASTRIGIN(30,    72.859 , 11.196281345516404),
    TC_RASTRIGIN(30,   100     , 11.512925464970228),
    TC_RASTRIGIN(30,   128     , 11.759785542901755),
    TC_RASTRIGIN(30,   256     , 12.4529327234617  ),
    TC_RASTRIGIN(30,   512     , 13.146079904021645),
    TC_RASTRIGIN(30,  1024     , 13.83922708458159 ),
    TC_RASTRIGIN(30,  2048     , 14.532374265141536),
    TC_RASTRIGIN(30,  4096     , 15.225521445701482),
  };

  for(auto &fd : testfuncs) {
    if(enabled_tests & RANDOM_SEARCH) {
      randsearch::search_parameters param { max_steps, popsize, fd.dimensionality, fd.limit_pos.min(), fd.limit_pos.max() };
      randsearch::technique tech(fd.func, param);
      simulation::run_simulation(tech, fd.tag, "randsearch", fd.simcount);
    }

    if(enabled_tests & GSA) {
      common::exponential_slide G_slide { max_steps, fd.alpha, fd.G0 };
      common::linear_slide      K_slide { max_steps, 1.0, 0.0 };

      gsa::search_parameters param { max_steps, popsize, fd.dimensionality,
				     fd.limit_pos, G_slide, K_slide };
      gsa::technique tech(fd.func, param);
      simulation::run_simulation(tech, fd.tag, "gsa", fd.simcount);
    }
  }
}
