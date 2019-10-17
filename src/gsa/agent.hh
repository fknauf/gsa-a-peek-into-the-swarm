#ifndef INCLUDED_GSA_AGENT_HH
#define INCLUDED_GSA_AGENT_HH

#include "search_parameters.hh"
#include "snapshot.hh"
#include <limits>

namespace gsa {
  class agent {
  public:    
    agent() = default;
    agent(function_type const &f,
          vector_type   const &position,
          vector_type   const &velocity,
	  bool                 use_pbest);

    snapshot    const &current      () const { return current_      ; }
    snapshot    const &personal_best() const { return personal_best_; }
    double             mass         () const { return mass_         ; }

    double             fitness      () const { return current_.fitness (); }
    vector_type const &position     () const { return current_.position(); }

    double             attractor_fitness() const;

    static void reset_ids();
    int id() const { return id_; }
    
    void update_velocity(std::size_t               step_nr,
                         std::vector<agent> const &sorted_population,
                         search_parameters  const &param,
                         rng_type                 &rng);

    void apply_velocity(function_type const &f,
                        search_parameters const &param,
                        rng_type &rng);

    void update_mass_pass1(double current_best, double current_worst);
    void update_mass_pass2(double sum_of_masses);

    void disrupt(function_type const &f,
		 double base,
		 double shift,
		 search_parameters const &param,
		 rng_type &rng);

    void disrupt2(double                   streuung,
		  function_type     const &f,
		  search_parameters const &param,
		  rng_type                &rng);

  private:
    snapshot const &attractor() const;
    
    vector_type &rand01_vector(rng_type &rng);

    void do_move(vector_type       const &new_pos,
		 function_type     const &f,
		 search_parameters const &param,
		 rng_type                &rng);

    int id_;

    bool        use_pbest_;
    snapshot    current_;
    snapshot    personal_best_;
    vector_type velocity_;
    
    double      mass_ = 0.0;

    std::uniform_real_distribution<> dist01_;
    vector_type scratch_rand_;
  };

  bool is_fitter(agent const &lhs, agent const &rhs);
}

#endif
