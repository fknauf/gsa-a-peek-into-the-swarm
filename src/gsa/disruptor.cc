#include "disruptor.hh"

#include "agent.hh"
#include "search_parameters.hh"

#include <common/common.hh>

namespace gsa {
  disruptor::disruptor(disruption_type type)
    : type_(type)
  { }

  disruptor::disruptor(disruption_type type, std::size_t max_step, double theta, double rho)
    : disruptor(type, common::linear_slide(max_step, theta, 0), rho)
  { }

  disruptor::disruptor(disruption_type type, std::function<double(std::size_t)> C_slide, double rho)
    : type_(type),
      C_slide_(C_slide),
      rho_(rho)
  { }

  void disruptor::apply(std::size_t          step,
			function_type const &f,
			std::vector<agent>  &population,
			search_parameters   &param,
			rng_type            &rng) const
  {
    switch(type_) {
    case DISABLED:
      break;
    case ORIGINAL:
      {
	double C = C_slide_(step);
	std::sort(begin(population), end(population), is_fitter);
    
	agent const &best = population.front();
    
	for(std::size_t i = 1; i < population.size(); ++i) {
	  agent const &prev = population[i - 1];
	  agent       &cur  = population[i    ];

	  double R = (best.position() - cur.position()).norm();
	  double r = (prev.position() - cur.position()).norm();

	  if(r / R < C) {
	    if(R <= 1) {
	      cur.disrupt(f, 0.0, r, param, rng);
	    } else {
	      cur.disrupt(f, 1.0, rho_, param, rng);
	    }
	  }
	}
      }
      break;
    case SHIFT_STREUUNG:
      // Fehlgeschlagener Versuch, von GSA-Disrupt etwas zu retten.      
      {
	double C = C_slide_(step);
	std::sort(begin(population), end(population), is_fitter);

	double sqsum = 0.0;
	agent const &best = population.front();

	for(std::size_t i = 1; i < population.size(); ++i) {
	  auto diff = best.position() - population[i].position();
	  sqsum += diff.squaredNorm();
	}

	double streuung = std::sqrt(sqsum / population.size()) * rho_;

	for(std::size_t i = 2; i < population.size(); ++i) {
	  agent const &prev = population[i - 1];
	  agent       &cur  = population[i    ];

	  double R = (best.position() - cur.position()).norm();
	  double r = (prev.position() - cur.position()).norm();

	  if(r / R < C) {
	    cur.disrupt2(streuung, f, param, rng);
	  }
	}
      }
    }
  }
}
