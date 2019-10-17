#include "slide.hh"

#include <cmath>

namespace common {
  slide::slide(std::size_t max_step) : max_step_(max_step) { }
  slide::~slide() { }

  double slide::t(std::size_t step) const {
    return double(step) / max_step_;
  }

  constant_slide::constant_slide(double value) : slide(0), value_(value) { }

  double constant_slide::operator()(std::size_t) const {
    return value_;
  }
  
  linear_slide::linear_slide(std::size_t max_step, double start, double end)
    : slide(max_step), start_(start), end_(end)
  { }

  double linear_slide::operator()(std::size_t step) const {
    return start_ + (end_ - start_) * t(step);
  }

  exponential_slide::exponential_slide(std::size_t max_step, double alpha, double G0)
    : slide(max_step), alpha_(alpha), G0_(G0)
  { }
    
  double exponential_slide::operator()(std::size_t step) const {
    return G0_ * std::exp(-alpha_ * t(step));
  }
}
