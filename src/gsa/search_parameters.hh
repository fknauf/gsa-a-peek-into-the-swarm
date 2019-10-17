#ifndef INCLUDED_GSA_SEARCH_PARAMETERS_HH
#define INCLUDED_GSA_SEARCH_PARAMETERS_HH

#include "disruptor.hh"
#include "types.hh"
#include <atomic>
#include <common/common.hh>
#include <cstddef>

namespace gsa {
  extern std::atomic<int> displacements;
  
  class search_parameters {
  public:
    search_parameters(std::size_t    max_steps,
		      std::size_t    population_size,
		      index_type     dimensions,
		      common::limits limits_position,
		      double         G0,
		      double         alpha,
		      double         epsilon = 1e-16);

    search_parameters(std::size_t                        max_steps,
		      std::size_t                        population_size,
		      index_type                         dimensions,
		      common::limits                     limits_position,
		      std::function<double(std::size_t)> G_slide,
		      std::function<double(std::size_t)> K_slide,
		      disruptor                          disrupt = disruptor(),
		      bool                               use_personal_best = false,
		      double                             epsilon = 1e-16);

    std::size_t max_steps        () const { return max_steps_ ; }
    std::size_t population_size  () const { return pop_size_  ; }
    index_type  dimensions       () const { return dimensions_; }
    bool        use_personal_best() const { return use_pbest_ ; }
    double      epsilon          () const { return epsilon_   ; }

    common::limits const &limits_position() const { return limits_pos_; }

    vector_type random_position(rng_type &rng) const;
    vector_type initial_velocity(rng_type &rng) const;

    vector_type fixed_position(vector_type const &pos, rng_type &rng) const;

    double      G(std::size_t step) const;
    std::size_t K(std::size_t step) const;
    disruptor const &disruption() const { return disruptor_; }

    bool out_of_bounds(vector_type const &position) const;
    
  private:
    std::size_t    max_steps_;
    std::size_t    pop_size_;
    index_type     dimensions_;
    common::limits limits_pos_;

    std::function<double(std::size_t)> G_slide_;
    std::function<double(std::size_t)> K_slide_;

    disruptor disruptor_;

    bool   use_pbest_;
    double epsilon_;
  };
}

#endif
