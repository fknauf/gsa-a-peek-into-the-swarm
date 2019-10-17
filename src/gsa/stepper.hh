#ifndef INCLUDED_GSA_STEPPER_HH
#define INCLUDED_GSA_STEPPER_HH

#include "agent.hh"

namespace gsa {
  class stepper {
  public:
    stepper(function_type     const &f,
	    search_parameters const &param);

    void step();
    agent const &current_best() const { return current_best_; }
    agent const &global_best () const { return global_best_; }

    std::vector<agent> const &population() const { return population_; }

  private:
    function_type      f_;
    search_parameters  param_;

    rng_type           rng_;
    std::vector<agent> population_;
    agent              current_best_;
    agent              global_best_;

    std::size_t        step_ = 0;
  };
}

#endif
