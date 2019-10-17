#ifndef INCLUDED_RANDOM_AGENT_HH
#define INCLUDED_RANDOM_AGENT_HH

#include "search_parameters.hh"
#include <limits>

namespace randsearch {
  class agent {
  public:
    agent() = default;
    agent(function_type const &f, vector_type const &pos);

    vector_type const &position() const { return position_; }
    double             fitness () const { return fitness_ ; }

  private:
    vector_type position_;
    double      fitness_ = std::numeric_limits<double>::infinity();
  };
}

#endif
