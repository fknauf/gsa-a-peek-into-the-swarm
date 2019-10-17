#include "common/common.hh"
#include "testfunc.hh"

#include "random/random_search.hh"
#include "gsa/gsa.hh"

#include <sys/stat.h>
#include <sys/types.h>

#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

namespace simulation {
  std::string const OUTPUT_ROOT = "output/swarmpositions/";
  
  template<typename Agents>
  std::pair<double, double> streuung(Agents const &swarm) {
    common::vector_type avg = common::vector_type::Zero(swarm.front().position().rows());
    
    for(auto && a : swarm) {
      avg += a.position() / swarm.size();
    }

    double variance = 0.0;
    double var_w = 0.0;
    
    for(auto && a : swarm) {
      variance += (a.position() - avg).squaredNorm() / swarm.size();
      var_w += (a.position() - swarm.front().position()).squaredNorm() / swarm.size();
    }

    return std::make_pair(std::sqrt(variance), std::sqrt(var_w));
  }

  template<typename Technique>
  void run_simulation(Technique   const &tech,
                      std::string const &tag_func,
                      std::string const &tag_verf)
  {
    // id mechanism is a bit hacky, was tacked on late.
    gsa::agent::reset_ids();
    
    auto stepper = tech.create_stepper();

    std::string output_path = OUTPUT_ROOT + tag_func;
    mkdir(output_path.c_str(), 0755);
    output_path += "/" + tag_verf;
    mkdir(output_path.c_str(), 0755);    
    
    std::cout << tag_func << "_" << tag_verf << ": " << std::string(20 - tag_verf.size(), ' ') << std::flush;
    std::clock_t start = std::clock();

    std::ofstream out_streuung((output_path + "/streuung.tsv").c_str());
    out_streuung << "step\tstdabw\tstdabw_w\n";

    std::vector<std::ofstream> particle_fds;
    for(std::size_t i = 0; i < tech.param().population_size(); ++i) {
      std::ostringstream fname;
      fname << output_path << "/particle" << std::setfill('0') << std::setw(2) << i << ".tsv";
      particle_fds.emplace_back(fname.str().c_str());
    }

    for(std::size_t step = 0; step < tech.max_steps(); ++step) {
      std::ostringstream fname;
      fname << output_path << "/positions." << std::setfill('0') << std::setw(3) << step << ".tsv";
      std::ofstream out(fname.str().c_str());

      auto s = streuung(stepper->population());
      out_streuung << step << "\t" <<  s.first << "\t" << s.second << "\n";
      
      for(auto a : stepper->population()) {
	out << std::setprecision(16) << a.position().transpose() << "\n";
	particle_fds.at(a.id()) << std::setprecision(16) << a.position().transpose() << std::endl;
      }

      stepper->step();
    }

    auto s = streuung(stepper->population());
    out_streuung << tech.max_steps() << "\t" <<  s.first << "\t" << s.second << "\n";  
    
    std::clock_t end = std::clock();
    std::cout << std::fixed << double(end - start) / CLOCKS_PER_SEC << " Sekunden"
	      << ", Best: " << stepper->global_best().fitness()
	      << "\n";
  }
}

enum {
      RANDOM_SEARCH = 1 <<  0,
      GSA           = 1 <<  1,
};

int main() {
  std::uint32_t enabled_tests = 0
    // | RANDOM_SEARCH
    | GSA                   
    ;  
  std::size_t        const max_steps = 1000;
  std::size_t        const popsize   =   50;
  common::index_type const dim       =    2;
  
  struct testcase {
    common::function_type func;
    std::string tag;
    common::limits limit_pos;
    common::index_type dimensionality = dim;

    double G0;
    double alpha;
  } testfuncs[] = {
		   { rosenbrock     , "rosenbrock_2_16", { -  2.048,  2.048  }, 2, 16.0, 21.19326946619214670981 },
		   { rastrigin      , "rastrigin_20_20", { -  5.12 ,  5.12   }, 2, 20.0, 20.0                    },
  };

  for(auto &fd : testfuncs) {
    if(enabled_tests & GSA) {
      common::exponential_slide G_slide { max_steps, fd.alpha, fd.G0 };
      common::linear_slide      K_slide { max_steps, 1.0, 0.0 };

      gsa::search_parameters param { max_steps, popsize, fd.dimensionality,
				     fd.limit_pos, G_slide, K_slide };
      gsa::technique tech(fd.func, param);
      simulation::run_simulation(tech, fd.tag,  "gsa");
    }
  }
}
