#include "limits.hh"

namespace common {
  limits::limits(double min, double max)
    : min_(min), max_(max), dist_(min, max)
  { }

  double limits::force(double x) const {
    return std::min(max_, std::max(min_, x));
  }
    
  double limits::random(rng_type &rng) const {
    return dist_(rng);
  }

  vector_type limits::random_vector(index_type dim, rng_type &rng) const {
    return common::random_vector(dim, dist_, rng);
  }

  vector_type &limits::randomize_vector(vector_type &dest, rng_type &rng) const {
    return common::randomize_vector(dest, dist_, rng);
  }  
  
  bool limits::contains(double x) const {
    return x >= min_ && x <= max_;
  }

  limits limits::shift(double offset) const {
    return { min() + offset, max() + offset };
  }

  double limits::mirror(double x) const {
    while(!contains(x)) {
      if(x > max()) {
	x = 2 * max() - x;
      } else if(x < min()) {
	x = 2 * min() - x;
      }
    }

    return x;
  }
}
