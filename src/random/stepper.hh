#ifndef INCLUDED_RANDOM_STEPPER_HH
#define INCLUDED_RANDOM_STEPPER_HH

#include "agent.hh"

namespace randsearch {
  class stepper {
  public:
    stepper(function_type     const &f,
	    search_parameters const &param);

    void step();

    agent const &current_best() const { return current_; }
    agent const &global_best () const { return best_   ; }
    
  private:
    vector_type &rand_vector();
    
    function_type f_;
    search_parameters param_;
    
    rng_type rng_;
    agent current_;
    agent best_;

    vector_type scratch_rand_;
  };
}

#endif
