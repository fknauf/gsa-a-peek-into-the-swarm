#include <common/limits.hh>

#include <boost/test/unit_test.hpp>
#include <random>

BOOST_AUTO_TEST_SUITE( ts_limits )

BOOST_AUTO_TEST_CASE( basic )  {
  common::limits lim(-10.0, 10.0);

  BOOST_CHECK_CLOSE(-10.0, lim.min(), 1e-10);
  BOOST_CHECK_CLOSE( 10.0, lim.max(), 1e-10);

  BOOST_CHECK_CLOSE(  2.0, lim.force(  2.0), 1e-10);
  BOOST_CHECK_CLOSE( 10.0, lim.force( 20.0), 1e-10);
  BOOST_CHECK_CLOSE(-10.0, lim.force(-20.0), 1e-10);

  BOOST_CHECK( lim.contains(  2.0));
  BOOST_CHECK( lim.contains( 10.0));
  BOOST_CHECK( lim.contains(-10.0));
  BOOST_CHECK(!lim.contains( 12.0));
  BOOST_CHECK(!lim.contains(-12.0));
  BOOST_CHECK(!lim.contains( 10.001));
  BOOST_CHECK(!lim.contains(-10.001));

  BOOST_CHECK_CLOSE( 2.0, lim.mirror(  2.0), 1e-10);
  BOOST_CHECK_CLOSE( 8.0, lim.mirror( 12.0), 1e-10);
  BOOST_CHECK_CLOSE(-8.0, lim.mirror(-12.0), 1e-10);
  BOOST_CHECK_CLOSE( 8.0, lim.mirror(-32.0), 1e-10); //double bounce
  BOOST_CHECK_CLOSE( 8.0, lim.mirror( 52.0), 1e-10);

  auto shifted = lim.shift(5.0);

  BOOST_CHECK_CLOSE(-5.0, shifted.min(), 1e-10);
  BOOST_CHECK_CLOSE(15.0, shifted.max(), 1e-10);
}

BOOST_AUTO_TEST_CASE( random ) {
  common::limits lim(-10.0, 10.0);

  {
    std::mt19937_64 rng;

    for(int i = 0; i < 1000; ++i) {
      double r = lim.random(rng);

      BOOST_CHECK_GE(r, lim.min());
      BOOST_CHECK_LE(r, lim.max());
    }
  }

  {
    std::mt19937_64 rng1;
    std::mt19937_64 rng2;

    auto rvec = lim.random_vector(3, rng1);

    BOOST_CHECK_CLOSE(lim.random(rng2), rvec(0), 1e-10);
    BOOST_CHECK_CLOSE(lim.random(rng2), rvec(1), 1e-10);
    BOOST_CHECK_CLOSE(lim.random(rng2), rvec(2), 1e-10);
  }

  {
    std::mt19937_64 rng1;
    std::mt19937_64 rng2;

    common::vector_type rvec(3);
    auto &ref = lim.randomize_vector(rvec, rng1);

    BOOST_CHECK(&ref == &rvec);

    BOOST_CHECK_CLOSE(lim.random(rng2), rvec(0), 1e-10);
    BOOST_CHECK_CLOSE(lim.random(rng2), rvec(1), 1e-10);
    BOOST_CHECK_CLOSE(lim.random(rng2), rvec(2), 1e-10);
  }
}

BOOST_AUTO_TEST_SUITE_END()
