#include "stepper.hh"

namespace gsa {
  stepper::stepper(function_type const &f, search_parameters const &param)
    : f_(f), param_(param), rng_(std::random_device{}())
  {

    for(std::size_t i = 0; i < param.population_size(); ++i) {
      population_.emplace_back(f,
                               param.random_position (rng_),
                               param.initial_velocity(rng_),
			       param.use_personal_best());
    }

    std::sort(begin(population_), end(population_), is_fitter);
    global_best_
      = current_best_
      = population_.front();
  }

  void stepper::step() {
    assert(population_.size() == param_.population_size());
    assert(std::is_sorted(begin(population_), end(population_), is_fitter));

    double current_best  = population_.front().attractor_fitness();
    double current_worst = population_.back ().attractor_fitness();
    double sum_of_masses = 0.0;
    double mass_testsum  = 0.0;

    assert(current_best <= current_worst);

    for(auto &a : population_) {
      a.update_mass_pass1(current_best, current_worst);
      sum_of_masses += a.mass();
    }

    for(auto &a : population_) {
      a.update_mass_pass2(sum_of_masses);
      mass_testsum += a.mass();
    }

    assert(std::abs(mass_testsum - 1) < 1e-7);

    for(auto &a : population_) {
      a.update_velocity(step_, population_, param_, rng_);
    }

    for(auto &a : population_) {
      a.apply_velocity(f_, param_, rng_);
    }

    ++step_;

    param_.disruption().apply(step_, f_, population_, param_, rng_);

    std::sort(begin(population_), end(population_), is_fitter);
    current_best_ = population_.front();

    if(current_best_.attractor_fitness() <= global_best_.attractor_fitness()) {
      global_best_ = current_best_;
    }
  }
}
