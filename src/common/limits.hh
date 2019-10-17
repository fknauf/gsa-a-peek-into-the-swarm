#ifndef INCLUDED_COMMON_LIMITS_HH
#define INCLUDED_COMMON_LIMITS_HH

#include "random.hh"
#include "types.hh"

#include <algorithm>

namespace common {
  class limits {
  public:
    limits(double min, double max);

    double min() const { return min_; }
    double max() const { return max_; }
    double force(double x) const;
    double random(rng_type &rng) const;
    double mirror(double x) const;
    bool   contains(double x) const;

    vector_type  random_vector(index_type dim, rng_type &rng) const;
    vector_type &randomize_vector(vector_type &dest, rng_type &rng) const;

    limits shift(double offset) const;
    
  private:
    double min_;
    double max_;
    mutable std::uniform_real_distribution<> dist_;
  };
}

#endif
