#ifndef INCLUDED_COMMON_MATH_HH
#define INCLUDED_COMMON_MATH_HH

namespace common {
  inline double square(double x) {
    return x * x;
  }

  inline double cube(double x) {
    return x * x * x;
  }
  
  double sigmoid(double x);
}

#endif
