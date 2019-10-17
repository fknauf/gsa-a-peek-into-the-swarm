#include "common.hh"

namespace common {
  vector_type &randomize_vector(vector_type       &dest,
				vector_type const &minvec,
				vector_type const &maxvec,
				rng_type          &rng)
  {
    assert(dest.rows() == minvec.rows());
    assert(dest.rows() == maxvec.rows());

    for(index_type i = 0; i < dest.rows(); ++i) {
      std::uniform_real_distribution<> dist(minvec(i), maxvec(i));
      dest(i) = dist(rng);
    }

    return dest;
  }

  vector_type random_vector(vector_type const &minvec,
			    vector_type const &maxvec,
			    rng_type          &rng)
  {
    vector_type result(minvec.rows());
    return randomize_vector(result, minvec, maxvec, rng);
  }

  vector_type random_vector(index_type dim, rng_type &rng) {
    std::uniform_real_distribution<> dist;
    return random_vector(dim, dist, rng);
  }
}
