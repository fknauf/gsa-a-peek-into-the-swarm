#include <gsa/search_parameters.hh>

#include <boost/test/unit_test.hpp>
#include <random>

BOOST_AUTO_TEST_SUITE( ts_gsa_searchparam )

BOOST_AUTO_TEST_CASE( basic )  {
  std::size_t               steps   = 100;
  std::size_t               popsize =  10;
  common::index_type        dim     =   3;
  double                    alpha   =  20.0;
  double                    G0      = 100.0;
  common::limits            poslimits(-10.0, 10.0);
  common::exponential_slide Gslide(steps, alpha, G0);
  common::linear_slide      Kslide(steps, 1, 0);

  gsa::search_parameters param(steps,
                               popsize,
                               dim,
                               poslimits,
                               Gslide,
                               Kslide);

  BOOST_CHECK_EQUAL(steps          , param.max_steps());
  BOOST_CHECK_EQUAL(popsize        , param.population_size());
  BOOST_CHECK_EQUAL(dim            , param.dimensions());
  BOOST_CHECK_CLOSE(poslimits.min(), param.limits_position().min(), 1e-10);
  BOOST_CHECK_CLOSE(poslimits.max(), param.limits_position().max(), 1e-10);

  {
    std::mt19937_64 rng1;

    auto rpos = param.random_position(rng1);

    BOOST_CHECK_EQUAL(dim, rpos.size());

    for(int i = 0; i < rpos.size(); ++i) {
      BOOST_CHECK(poslimits.contains(rpos(i)));
    }

    rpos(0) = poslimits.min() - 1.0;

    BOOST_CHECK(param.out_of_bounds(rpos));

    rpos = param.fixed_position(rpos, rng1);

    BOOST_CHECK(poslimits.contains(rpos(0)));
  }

  BOOST_CHECK_CLOSE(Gslide(10)          , param.G(10), 1e-10);
  BOOST_CHECK_CLOSE(Kslide(10) * popsize, param.K(10), 1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
