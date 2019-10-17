#ifndef INCLUDED_COMMON_TYPES_HH
#define INCLUDED_COMMON_TYPES_HH

#include <Eigen/Core>

#include <functional>
#include <random>

namespace common {
  using index_type    = Eigen::Index;
  using vector_type   = Eigen::VectorXd;
  using function_type = std::function<double(vector_type)>;
  using rng_type      = std::mt19937_64;
}

#endif
