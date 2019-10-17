#include <common/math.hh>

#include <boost/test/unit_test.hpp>
#include <random>

BOOST_AUTO_TEST_SUITE( ts_math )

BOOST_AUTO_TEST_CASE( basic )  {
  BOOST_CHECK_CLOSE(16.0, common::square( 4.0), 1e-10);
  BOOST_CHECK_CLOSE(16.0, common::square(-4.0), 1e-10);

  BOOST_CHECK_CLOSE( 64.0, common::cube( 4.0), 1e-10);
  BOOST_CHECK_CLOSE(-64.0, common::cube(-4.0), 1e-10);

  BOOST_CHECK_CLOSE(0.5, common::sigmoid(0), 1e-10);
  BOOST_CHECK_CLOSE(common::sigmoid(1.0) - 0.5, 0.5 - common::sigmoid(-1.0), 1e-10);
  BOOST_CHECK_CLOSE(common::sigmoid(2.0) - 0.5, 0.5 - common::sigmoid(-2.0), 1e-10);
  BOOST_CHECK_CLOSE(common::sigmoid(3.0) - 0.5, 0.5 - common::sigmoid(-3.0), 1e-10);

  BOOST_CHECK_CLOSE(1 / (1 + 1 / M_E), common::sigmoid(1.0), 1e-10);
  BOOST_CHECK_CLOSE(1 / (1 + 1 / M_E / M_E), common::sigmoid(2.0), 1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
