#include <common/slide.hh>

#include <boost/test/unit_test.hpp>
#include <random>

BOOST_AUTO_TEST_SUITE( ts_slide )

BOOST_AUTO_TEST_CASE( constant )  {
  common::constant_slide slide(2.0);

  BOOST_CHECK_CLOSE(2.0, slide(  0), 1e-10);
  BOOST_CHECK_CLOSE(2.0, slide( 10), 1e-10);
  BOOST_CHECK_CLOSE(2.0, slide(100), 1e-10);
}

BOOST_AUTO_TEST_CASE( linear )  {
  common::linear_slide slide(100.0, 2.0, 1.0);

  BOOST_CHECK_CLOSE(2.0, slide(  0), 1e-10);
  BOOST_CHECK_CLOSE(1.9, slide( 10), 1e-10);
  BOOST_CHECK_CLOSE(1.5, slide( 50), 1e-10);
  BOOST_CHECK_CLOSE(1.0, slide(100), 1e-10);
}

BOOST_AUTO_TEST_CASE( exponential )  {
  common::exponential_slide slide(100.0, 20.0, 5.0);

  BOOST_CHECK_CLOSE(5.0 * std::exp(-  0 / 100.0 * 20.0), slide(  0), 1e-10);
  BOOST_CHECK_CLOSE(5.0 * std::exp(- 10 / 100.0 * 20.0), slide( 10), 1e-10);
  BOOST_CHECK_CLOSE(5.0 * std::exp(- 50 / 100.0 * 20.0), slide( 50), 1e-10);
  BOOST_CHECK_CLOSE(5.0 * std::exp(-100 / 100.0 * 20.0), slide(100), 1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
