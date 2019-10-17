#ifndef INCLUDED_GSA_SNAPSHOT_HH
#define INCLUDED_GSA_SNAPSHOT_HH

#include "types.hh"
#include <limits>

namespace gsa {
  class snapshot {
  public:
    snapshot() = default;
    snapshot(function_type const &f, vector_type const &position)
      : position_(position), fitness_(f(position))
    { }

    vector_type const &position() const { return position_; }
    double             fitness () const { return fitness_ ; }

  private:
    vector_type position_;
    double      fitness_ = std::numeric_limits<double>::infinity();
  };
}

#endif
