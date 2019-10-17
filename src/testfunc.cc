#include "testfunc.hh"
#include <cmath>
#include "common/math.hh"

using common::square;

double griewank(common::vector_type const &pos) {
  double prod = 1;

  for(common::index_type i = 0; i < pos.rows(); ++i) {
    prod *= std::cos(pos(i) / std::sqrt(i + 1));
  }
  
  return 1 + pos.squaredNorm() / 4000 - prod;
}

double rastrigin(common::vector_type const &pos) {
  double A = 10.0;
  return A * pos.rows() + pos.squaredNorm() - A * (2 * M_PI * pos).array().cos().sum();
}

double rosenbrock(common::vector_type const &x) {
  double sum = 0.0;
  
  for(common::index_type i = 1; i < x.rows(); ++i) {
    sum += 100 * square(x(i) - square(x(i - 1))) + square(1 - x(i - 1));
  }

  return sum;
}

double styblinski_tang(common::vector_type const &x) {
  double sum = 0.0;

  for(common::index_type i = 0; i < x.rows(); ++i) {
    sum += square(square(x(i))) - 16 * square(x(i)) + 5 * x(i);
  }

  return 0.5 * sum;
}

double hoelder_table(common::vector_type const &pos) {
  double x = pos(0);
  double y = pos(1);

  if(x < -10 || x > 10 || y < -10 || y > 10) {
    return 9001;
  }
  
  return -std::abs(std::sin(x) * std::cos(y) * std::exp(std::abs(1 - pos.norm() / M_PI)));
}

double easom(common::vector_type const &pos) {
  double x = pos(0);
  double y = pos(1);

  return -std::cos(x) * std::cos(y) * std::exp(-common::square(x - M_PI) - common::square(y - M_PI));
}

double sphere_shift10(common::vector_type const &pos) {
  return (pos.array() + 10).matrix().squaredNorm();
}
