#ifndef INCLUDED_RANDOM_SEARCH_PARAMETERS_HH
#define INCLUDED_RANDOM_SEARCH_PARAMETERS_HH

#include "types.hh"

#include <common/common.hh>

namespace randsearch {
  class search_parameters {
  public:
    search_parameters(std::size_t max_steps,
		      std::size_t population_size,
		      index_type dimensions,
		      double minval,
		      double maxval);
    search_parameters(std::size_t max_steps,
		      std::size_t population_size,
		      vector_type const &minvec, vector_type const &maxvec);

    std::size_t max_steps      () const { return max_steps_; }
    std::size_t population_size() const { return popsize_; }
    vector_type const &min() const { return min_; }
    vector_type const &max() const { return max_; }

  private:
    std::size_t max_steps_;
    std::size_t popsize_;
    vector_type min_;
    vector_type max_;
  };  
}

#endif
