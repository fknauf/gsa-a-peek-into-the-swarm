#ifndef INCLUDED_RANDOM_TECHNIQUE_HH
#define INCLUDED_RANDOM_TECHNIQUE_HH

#include "stepper.hh"
#include <memory>

namespace randsearch {
  class technique {
  public:
    using stepper           = randsearch::stepper;
    using agent             = randsearch::agent;
    using search_parameters = randsearch::search_parameters;

    technique(function_type const &f, search_parameters const &param);
    
    std::unique_ptr<stepper> create_stepper() const;

    auto max_steps() const { return param_.max_steps(); }

  private:
    function_type     f_;
    search_parameters param_;
  };
}

#endif
