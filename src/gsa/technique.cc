#include "technique.hh"

namespace gsa {
  technique::technique(function_type const &f, search_parameters const &param)
    : f_(f), param_(param) { }

  std::unique_ptr<stepper> technique::create_stepper() const {
    return std::make_unique<stepper>(f_, param_);
  }
}
