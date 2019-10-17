#ifndef INCLUDED_COMMON_HH
#define INCLUDED_COMMON_HH

#include "types.hh"
#include <random>

namespace common {
  template<typename Distribution>
  vector_type &randomize_vector(vector_type &v, Distribution &dist, rng_type &rng) {
    for(index_type i = 0; i < v.rows(); ++i) {
      v(i) = dist(rng);
    }

    return v;
  }
  
  template<typename Distribution>
  vector_type random_vector(index_type dim, Distribution &dist, rng_type &rng) {
    vector_type result(dim);
    return randomize_vector(result, dist, rng);
  }
  
  vector_type random_vector(index_type dim, rng_type &rng);
  vector_type random_vector(vector_type const &minvec,
			    vector_type const &maxvec,
			    rng_type          &rng);

  vector_type &randomize_vector(vector_type       &dest,
				vector_type const &minvec,
				vector_type const &maxvec,
				rng_type          &rng);
}

#endif
