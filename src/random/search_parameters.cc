#include "search_parameters.hh"

namespace randsearch {
  search_parameters::search_parameters(std::size_t max_steps,
				       std::size_t popsize,
				       index_type  dimensions,
				       double      minval,
				       double      maxval)
    : search_parameters(max_steps,
			popsize,
			vector_type::Constant(dimensions, minval),
			vector_type::Constant(dimensions, maxval))
  { }
  
  search_parameters::search_parameters(std::size_t        max_steps,
				       std::size_t        population_size,
				       vector_type const &minvec,
				       vector_type const &maxvec)
    : max_steps_(max_steps),
      popsize_  (population_size),
      min_      (minvec),
      max_      (maxvec)
  {
    assert(min_.rows() == max_.rows());
  }
}
