#ifndef INCLUDED_GSA_TECHNIQUE_HH
#define INCLUDED_GSA_TECHNIQUE_HH

#include "stepper.hh"
#include <memory>

namespace gsa {
  class technique {
  public:
    using stepper           = gsa::stepper;
    using agent             = gsa::agent;
    using search_parameters = gsa::search_parameters;

    technique(function_type const &f, search_parameters const &param);
    
    std::unique_ptr<stepper> create_stepper() const;
    auto max_steps() const { return param_.max_steps(); }

    search_parameters const &param() const { return param_; }

  private:
    function_type     f_;
    search_parameters param_;    
  };  
}

#endif
