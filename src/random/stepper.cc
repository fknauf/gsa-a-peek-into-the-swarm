#include "stepper.hh"

namespace randsearch {
  stepper::stepper(function_type const &f, search_parameters const &param)
    : f_(f),
      param_(param),
      rng_(std::random_device{}()),
      scratch_rand_(param.min())
  {
  }

  vector_type &stepper::rand_vector() {
    return common::randomize_vector(scratch_rand_, param_.min(), param_.max(), rng_);
  }
  
  void stepper::step() {
    current_ = agent(f_, rand_vector());

    for(std::size_t i = 1; i < param_.population_size(); ++i) {      
      agent a(f_, rand_vector());
      if(a.fitness() < current_.fitness()) {
	current_ = a;
      }
    }

    if(current_.fitness() < best_.fitness()) {
      best_ = current_;
    }
  }
}
