#include "search_parameters.hh"

namespace gsa {
  std::atomic<int> displacements { 0 };

  search_parameters::search_parameters(std::size_t                        max_steps,
				       std::size_t                        population_size,
				       index_type                         dimensions,
				       common::limits                     limits_position,
				       std::function<double(std::size_t)> G_slide,
				       std::function<double(std::size_t)> K_slide,
				       disruptor                          disrupt,
				       bool                               use_personal_best,
				       double                             epsilon)
    : max_steps_(max_steps),
      pop_size_(population_size),
      dimensions_(dimensions),
      limits_pos_(limits_position),
      G_slide_(G_slide),
      K_slide_(K_slide),
      disruptor_(disrupt),
      use_pbest_(use_personal_best),
      epsilon_(epsilon) {
  }
      
  search_parameters::search_parameters(std::size_t    max_steps,
				       std::size_t    population_size,
				       index_type     dimensions,
				       common::limits limits_position,
				       double         G0,
				       double         alpha,
				       double         epsilon)
    : search_parameters(max_steps, population_size, dimensions, limits_position,
			common::exponential_slide(max_steps, alpha, G0),
			common::linear_slide(max_steps, 1.0, 0.0),
			disruptor(),
			epsilon)
  { }

  double search_parameters::G(std::size_t step) const {
    return G_slide_(step);
  }

  std::size_t search_parameters::K(std::size_t step) const {
    return std::size_t(std::ceil(population_size() * K_slide_(step)));
  }

  bool search_parameters::out_of_bounds(vector_type const &position) const {
    return position.minCoeff() < limits_position().min()
        || position.maxCoeff() > limits_position().max();
  }

  vector_type search_parameters::initial_velocity(rng_type &) const {
    return vector_type::Zero(dimensions());
  }

  vector_type search_parameters::random_position(rng_type &rng) const {
    return limits_position().random_vector(dimensions_, rng);
  }

  vector_type search_parameters::fixed_position(vector_type const &pos_p, rng_type &rng) const {
    ++displacements;
    //return random_position(rng);
    
    vector_type pos = pos_p;
  
    for(index_type i = 0; i < pos.rows(); ++i) {
      // Original
      
      if(!limits_position().contains(pos(i))) {
       	pos(i) = limits_position().random(rng);
      }

      // Variante B
      // static_cast<void>(rng);
      // pos(i) = limits_position().mirror(pos(i));
    }

    return pos;
  }
}
