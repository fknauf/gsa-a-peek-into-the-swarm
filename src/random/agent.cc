#include "agent.hh"

namespace randsearch {
  agent::agent(function_type const &f, vector_type const &pos)
    : position_(pos), fitness_(f(pos))
  { }
}
