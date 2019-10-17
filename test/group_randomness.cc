#include <common/random.hh>

#include <boost/test/unit_test.hpp>
#include <random>

BOOST_AUTO_TEST_SUITE( ts_random )

BOOST_AUTO_TEST_CASE( with_dist )  {
  std::mt19937_64 rng1;
  std::mt19937_64 rng2;
  std::mt19937_64 rng3;

  // normal_distribution can be stateful, so we need fresh ones to compare.
  std::normal_distribution<> dist1;
  std::normal_distribution<> dist2;
  std::normal_distribution<> dist3;

  common::vector_type rvec(3);

  common::randomize_vector(rvec, dist1, rng1);

  BOOST_CHECK_CLOSE(dist2(rng2), rvec(0), 1e-10);
  BOOST_CHECK_CLOSE(dist2(rng2), rvec(1), 1e-10);
  BOOST_CHECK_CLOSE(dist2(rng2), rvec(2), 1e-10);

  auto rvec2 = common::random_vector(3, dist3, rng3);

  BOOST_CHECK_CLOSE(rvec(0), rvec2(0), 1e-10);
  BOOST_CHECK_CLOSE(rvec(1), rvec2(1), 1e-10);
  BOOST_CHECK_CLOSE(rvec(2), rvec2(2), 1e-10);
}

BOOST_AUTO_TEST_CASE( standard_random ) {
  std::mt19937_64 rng1;
  std::mt19937_64 rng2;

  std::uniform_real_distribution<> dist(0, 1);

  auto rvec0 = common::random_vector(3,       rng1);
  auto rvec1 = common::random_vector(3, dist, rng2);

  BOOST_CHECK_CLOSE(rvec0(0), rvec1(0), 1e-10);
  BOOST_CHECK_CLOSE(rvec0(1), rvec1(1), 1e-10);
  BOOST_CHECK_CLOSE(rvec0(2), rvec1(2), 1e-10);
}

BOOST_AUTO_TEST_CASE( veclimit_random ) {
  std::mt19937_64 rng1;
  std::mt19937_64 rng2;

  common::vector_type minvec(3);
  common::vector_type maxvec(3);

  minvec << -4, -2, 3;
  maxvec << -2,  0, 5;

  std::uniform_real_distribution<> dist0(minvec(0), maxvec(0));
  std::uniform_real_distribution<> dist1(minvec(1), maxvec(1));
  std::uniform_real_distribution<> dist2(minvec(2), maxvec(2));

  auto rvec = common::random_vector(minvec, maxvec, rng1);

  BOOST_CHECK_CLOSE(dist0(rng2), rvec(0), 1e-10);
  BOOST_CHECK_CLOSE(dist1(rng2), rvec(1), 1e-10);
  BOOST_CHECK_CLOSE(dist2(rng2), rvec(2), 1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
