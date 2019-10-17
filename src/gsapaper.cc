#include "testfunc.hh"
#include "common/math.hh"

#include <random>

namespace {
  double u(double x, double a, double k, double m) {
    double xabs = std::abs(x);
    return xabs > a ? k * std::pow(xabs - a, m) : 0;
  }
}

using common::square;

double gsapaper_f1(common::vector_type const &x) {
  return x.squaredNorm();
}

double gsapaper_f2(common::vector_type const &x) {
  double s = 0.0, p = 1.0;

  for(int i = 0; i < x.rows(); ++i) {
    s += std::abs(x(i));
    p *= std::abs(x(i));
  }

  return s + p;
}

double gsapaper_f3(common::vector_type const &x) {
  double r = 0.0;

  for(int i = 0; i < x.rows(); ++i) {
    double s = 0.0;

    for(int j = 0; j < i; ++j) {
      s += x(j);
    }

    r += s * s;
  }

  return r;
}

double gsapaper_f4(common::vector_type const &x) {
  return x.cwiseAbs().maxCoeff();
}

double gsapaper_f5(common::vector_type const &x) {
  double sum = 0;

  for(int i = 0; i + 1 < x.rows(); ++i) {
    sum += 100 * square(x(i + 1) - square(x(i))) + square(x(i) - 1);
  }

  return sum;
}

double gsapaper_f6(common::vector_type const &x) {
  double sum = 0.0;

  for(int i = 0; i < x.rows(); ++i) {
    sum += square(x(i) + 0.5);
  }

  return sum;
}

double gsapaper_f7(common::vector_type const &x) {
  static std::mt19937_64 rng(std::random_device{}());
  std::uniform_real_distribution<> dist;

  double sum = 0.0;

  for(int i = 0; i < x.rows(); ++i) {
    sum += square(square(x(i)));
  }

  return sum + dist(rng);
}

double gsapaper_f8(common::vector_type const &x) {
  double sum = 0.0;

  for(int i = 0; i < x.rows(); ++i) {
    if(x(i) < -500) {
      return -x(i);
    } else if(x(i) > 500) {
      return x(i);
    }

    sum += -x(i) * std::sin(std::sqrt(std::abs(x(i))));
  }

  return sum;
}

double gsapaper_f9(common::vector_type const &x) {
  double sum = 0.0;

  for(int i = 0; i < x.rows(); ++i) {
    sum += square(x(i)) - 10 * std::cos(2 * M_PI * x(i)) + 10;
  }

  return sum;
}

double gsapaper_f10(common::vector_type const &x) {
  double sum = 0.0;

  for(int i = 0; i < x.rows(); ++i) {
    sum += std::cos(2 * M_PI * x(i));
  }

  return -20 * std::exp(-0.2 * std::sqrt(x.squaredNorm() / x.rows())) - std::exp(sum / x.rows()) + 20 + std::exp(1);
}

double gsapaper_f11(common::vector_type const &x) {
  double s = 0;
  double p = 1;

  for(int i = 0; i < x.rows(); ++i) {
    s += square(x(i));
    p *= std::cos(x(i) / std::sqrt(i + 1));
  }

  return s / 4000 - p + 1;
}

double gsapaper_f12(common::vector_type const &x) {
  int n = x.rows();

  double s1 = 0;
  double s2 = 0;

  double y0 = 1. + (x(0) + 1.) / 4.;
  double yi;
  double yi1 = y0;

  for(int i = 1; i < x.rows(); ++i) {
    yi = yi1;
    yi1 = 1. + (x(i) + 1.) / 4.;

    s1 += square(yi - 1) * (1 + 10 * square(std::sin(M_PI * yi1)));
  }

  for(int i = 0; i < x.rows(); ++i) {
    s2 += u(x(i), 10, 100, 4);
  }

  return M_PI / n * (10 * square(std::sin(M_PI * y0))
                     + s1
                     + square(yi1 - 1)) + s2;
}

double gsapaper_f13(common::vector_type const &x) {
  double s1 = 0;
  double s2 = 0;

  for(int i = 0; i < x.rows(); ++i) {
    // Formel im Paper falsch gesetzt: Gesetzt so:
    // s1 += square(x(i) - 1) * (1 + square(std::sin(3 * M_PI * x(i) + 1)));
    s2 += u(x(i), 5, 100, 4);
  }

  for(int i = 1; i < x.rows(); ++i) {
    // Im Matlab-Code so:

    s1 += square(x(i - 1) - 1) * (1 + square(std::sin(3 * M_PI * x(i))));
  }

  double xn = x(x.rows() - 1);

  return 0.1 * (square(std::sin(3 * M_PI * x(0)))
                + s1
                + square(xn - 1) * (1 + square(std::sin(2 * M_PI * xn))))
    + s2;
}

double gsapaper_f14(common::vector_type const &x) {
  double const a[2][25] = {
    { -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32, -32, -16, 0, 16, 32 },
    { -32, -32, -32, -32, -32, -16, -16, -16, -16, -16, 0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 32, 32, 32, 32, 32 }
  };

  double sum = 0;

  for(int j = 1; j <= 25; ++j) {
    sum += 1 / (j + std::pow(x(0) - a[0][j - 1], 6) + std::pow(x(1) - a[1][j - 1], 6));
  }

  return 1 / (1. / 500. + sum);
}

double gsapaper_f15(common::vector_type const &x) {
  double const aK[] = { .1957, .1947, .1735, .16, .0844, .0627, .0456, .0342, .0323, .0235, .0246 };
  double const bK[] = { 4, 2, 1, 0.5, 0.25, 1./6., 0.125, 0.1, 1./12., 1./14., 0.0625 };

  double sum = 0;

  for(int i = 0; i < 11; ++i) {
    double a = aK[i];
    double b = bK[i];

    sum += square(a - (x(0) * (square(b) + b * x(1))) / (square(b) + b * x(2) + x(3)));
  }

  return sum;
}

double gsapaper_f16(common::vector_type const &x) {
  return
    4 * square(x(0))
    - 2.1 * std::pow(x(0), 4)
    + std::pow(x(0), 6) / 3
    + x(0) * x(1)
    - 4 * square(x(1))
    + 4 * std::pow(x(1), 4)
    ;
}

double gsapaper_f17(common::vector_type const &x) {
  return
    square(x(1) - 1.275 * square(x(0) / M_PI) + 5 * x(0) / M_PI - 6)
    + 10 * (1 - 0.125 / M_PI) * std::cos(x(0))
    + 10;
    ;
}

double gsapaper_f18(common::vector_type const &x) {
  return
    (1 + square(x(0) + x(1) + 1)
     * (19 - 14 * x(0) + 3 * square(x(0)) - 14 * x(1) + 6 * x(0) * x(1) + 3 * square(x(1))))
    * (30 + square(2 * x(0) - 3 * x(1))
       * (18 - 32 * x(0) + 12 * square(x(0)) + 48 * x(1) - 36 * x(0) * x(1) + 27 * square(x(1))));
    ;
}

double gsapaper_f19(common::vector_type const &x) {
  double const aH[][3] = {
    {  3, 10, 30 },
    { .1, 10, 35 },
    {  3, 10, 30 },
    { .1, 10, 35 }
  };

  double const pH[][3] = {
    { .3689, .117, .2673 },
    { .4699, .4387, .747 },
    { .1091, .8732, .5547 },
    { .03815, .5743, .8828 }
  };

  double const cH[] = { 1, 1.2, 3, 3.2 };

  double sum = 0;

  for(int i = 0; i < 4; ++i) {
    double inner = 0;
    double const (&ai)[3] = aH[i];
    double const (&pi)[3] = pH[i];

    for(int j = 0; j < 3; ++j) {
      inner += ai[j] * square(x(j) - pi[j]);
    }

    sum += cH[i] * std::exp(-inner);
  }

  return -sum;
}

double gsapaper_f20(common::vector_type const &x) {
  double const aH[][6] = {
    { 10, 3, 17, 3.5, 1.7, 8 },
    { .05, 10, 17, .1, 8, 14 },
    { 3, 3.5, 1.7, 10, 17, 8 },
    { 17, 8, .05, 10, .1, 14 }
  };

  double const pH[][6] = {
    { .1312, .1696, .5569, .0124, .8283, .5886 },
    { .2329, .4135, .8307, .3736, .1004, .9991 },
    { .2348, .1415, .3522, .2883, .3047, .6650 },
    { .4047, .8828, .8732, .5743, .1091, .0381 }
  };

  double const cH[] = { 1, 1.2, 3, 3.2 };

  double sum = 0;

  for(int i = 0; i < 4; ++i) {
    double inner = 0;
    double const (&ai)[6] = aH[i];
    double const (&pi)[6] = pH[i];

    for(int j = 0; j < 6; ++j) {
      inner += ai[j] * square(x(j) - pi[j]);
    }

    sum += cH[i] * std::exp(-inner);
  }

  return -sum;
}

namespace {
  Eigen::Vector4d const aSH[] = {
    { 4, 4, 4, 4 },
    { 1, 1, 1, 1 },
    { 8, 8, 8, 8 },
    { 6, 6, 6, 6 },
    { 3, 7, 3, 7 },
    { 2, 9, 2, 9 },
    { 5, 5, 3, 3 },
    { 8, 1, 8, 1 },
    { 6, 2, 6, 2 },
    { 7, 3.6, 7, 3.6 }
  };

  double const cSH[] = { .1, .2, .2, .4, .4, .6, .3, .7, .5, .5 };
}

double gsapaper_f21(common::vector_type const &x) {
  double fit = 0;

  for(int i = 0; i < 5; ++i) {
    fit -= 1. / ((x - aSH[i]).squaredNorm() + cSH[i]);
  }

  return fit;
}

double gsapaper_f22(common::vector_type const &x) {
  double fit = 0;

  for(int i = 0; i < 7; ++i) {
    fit -= 1. / ((x - aSH[i]).squaredNorm() + cSH[i]);
  }

  return fit;
}

double gsapaper_f23(common::vector_type const &x) {
  double fit = 0;

  for(int i = 0; i < 10; ++i) {
    fit -= 1. / ((x - aSH[i]).squaredNorm() + cSH[i]);
  }

  return fit;
}
