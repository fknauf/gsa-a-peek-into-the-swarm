#ifndef INCLUDED_TESTFUNC_HH
#define INCLUDED_TESTFUNC_HH

#include "common/types.hh"

double griewank       (common::vector_type const &pos);
double rastrigin      (common::vector_type const &pos);
double rosenbrock     (common::vector_type const &pos);
double styblinski_tang(common::vector_type const &pos);
double hoelder_table  (common::vector_type const &pos);
double easom          (common::vector_type const &pos);
double sphere_shift10 (common::vector_type const &pos);

double gsapaper_f1 (common::vector_type const &x);
double gsapaper_f2 (common::vector_type const &x);
double gsapaper_f3 (common::vector_type const &x);
double gsapaper_f4 (common::vector_type const &x);
double gsapaper_f5 (common::vector_type const &x);
double gsapaper_f6 (common::vector_type const &x);
double gsapaper_f7 (common::vector_type const &x);
double gsapaper_f8 (common::vector_type const &x);
double gsapaper_f9 (common::vector_type const &x);
double gsapaper_f10(common::vector_type const &x);
double gsapaper_f11(common::vector_type const &x);
double gsapaper_f12(common::vector_type const &x);
double gsapaper_f13(common::vector_type const &x);
double gsapaper_f14(common::vector_type const &x);
double gsapaper_f15(common::vector_type const &x);
double gsapaper_f16(common::vector_type const &x);
double gsapaper_f17(common::vector_type const &x);
double gsapaper_f18(common::vector_type const &x);
double gsapaper_f19(common::vector_type const &x);
double gsapaper_f20(common::vector_type const &x);
double gsapaper_f21(common::vector_type const &x);
double gsapaper_f22(common::vector_type const &x);
double gsapaper_f23(common::vector_type const &x);

#endif
