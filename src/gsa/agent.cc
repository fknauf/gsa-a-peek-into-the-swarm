#include "agent.hh"

namespace gsa {
  namespace {
    int nextid = 0;
    
    int generate_id() {
      return nextid++;
    }
  }

  void agent::reset_ids() {
    nextid = 0;
  }
  
  agent::agent(function_type const &f,
               vector_type   const &position,
               vector_type   const &velocity,
	       bool                 use_pbest)
    : id_(generate_id()),
      use_pbest_(use_pbest),
      current_(f, position),
      personal_best_(current_),
      velocity_(velocity),
      scratch_rand_(position)
  { }

  double agent::attractor_fitness() const {
    return attractor().fitness();
  }

  void agent::update_velocity(std::size_t               step_nr,
                              std::vector<agent> const &sorted_population,
                              search_parameters  const &param,
                              rng_type                 &rng)
  {
    vector_type Fi = vector_type::Zero(velocity_.rows());

    auto G = param.G(step_nr);
    auto K = param.K(step_nr);

    for(std::size_t i = 0; i < K; ++i) {
      auto &other = sorted_population[i];

      if(this == &other) {
        continue;
      }

      auto dx = other.attractor().position() - position();

      // Vereinfachung nach (3.2)
      Fi += rand01_vector(rng).cwiseProduct(G * other.mass() * dx.normalized());

      // Ohne Vereinfachung
      // Fi += rand01_vector(rng).cwiseProduct(G * other.mass() / (dx.norm() + param.epsilon()) * dx);
    }

    velocity_ = rand01_vector(rng).cwiseProduct(velocity_) + Fi;
  }

  void agent::apply_velocity(function_type     const &f,
                             search_parameters const &param,
                             rng_type                &rng) {
    do_move(current_.position() + velocity_, f, param, rng);
  }

  void agent::do_move(vector_type       const &new_pos,
		      function_type     const &f,
		      search_parameters const &param,
		      rng_type                &rng)
  {
    current_ = snapshot(f, new_pos);

    if(param.out_of_bounds(current_.position())) {
      current_ = snapshot(f, param.fixed_position(current_.position(), rng));
      //velocity_ = param.initial_velocity(rng);
    }

    if(current_.fitness() <= personal_best_.fitness()) {
      personal_best_ = current_;
    }
  }

  void agent::update_mass_pass1(double current_best, double current_worst) {
    if(current_worst > current_best) {
      mass_ = (attractor_fitness() - current_worst) / (current_best - current_worst);
    } else {
      assert(current_worst == current_best);
      mass_ = 1.0;
    }
  }

  void agent::update_mass_pass2(double sum_of_masses) {
    mass_ /= sum_of_masses;
    assert(mass_ <= 1.0);
  }

  vector_type &agent::rand01_vector(rng_type &rng) {
    return common::randomize_vector(scratch_rand_, dist01_, rng);
  }

  snapshot const &agent::attractor() const {
    return use_pbest_ ? personal_best_ : current_;
  }

  void agent::disrupt(function_type const &f,
                      double base,
                      double shift,
		      search_parameters const &param,
                      rng_type &rng)
  {
    std::uniform_real_distribution<> dist0505 { -0.5, 0.5 };

    vector_type new_pos = position();

    double D = base + shift * dist0505(rng);
    for(index_type i = 0; i < new_pos.rows(); ++i) {
      new_pos(i) *= D;
    }

    do_move(new_pos, f, param, rng);
  }

  void agent::disrupt2(double                   streuung,
		       function_type     const &f,
		       search_parameters const &param,
		       rng_type                &rng)
  {
    std::uniform_real_distribution<> dist { -1, 1 };
    vector_type direction = common::random_vector(position().rows(), rng).normalized();

    do_move(position() + direction * streuung, f, param, rng);
  }
  
  bool is_fitter(agent const &lhs, agent const &rhs) {
    return lhs.attractor_fitness() < rhs.attractor_fitness();
  }
}
