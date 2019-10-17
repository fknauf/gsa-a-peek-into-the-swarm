#ifndef INCLUDED_GSA_DISRUPTOR_HH
#define INCLUDED_GSA_DISRUPTOR_HH

#include "types.hh"

#include <functional>
#include <vector>

namespace gsa {
  class agent;
  class search_parameters;
  
  class disruptor {
  public:
    enum disruption_type {
      DISABLED,
      ORIGINAL,
      SHIFT_STREUUNG
    };
    
    disruptor(disruption_type type = DISABLED);
    disruptor(disruption_type type, std::size_t max_step, double theta, double rho = 1e-16);
    disruptor(disruption_type type, std::function<double(std::size_t)> C_slide, double rho = 1e-16);

    void apply(std::size_t          step,
	       function_type const &f,
	       std::vector<agent>  &sorted_population,
	       search_parameters   &params,
	       rng_type            &rng) const;
    
  private:
    disruption_type type_ = DISABLED;
    
    std::function<double(std::size_t)> C_slide_;
    double rho_;
  };
}

#endif
