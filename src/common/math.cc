#include "math.hh"
#include <cmath>

namespace common { 
  double sigmoid(double x) {
    return 1 / (1 + std::exp(-x));
  }
}
