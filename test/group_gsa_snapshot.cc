#include <gsa/snapshot.hh>

#include <boost/test/unit_test.hpp>
#include <random>

BOOST_AUTO_TEST_SUITE( ts_gsa_snapshot )

BOOST_AUTO_TEST_CASE( basic )  {
  auto f = [](common::vector_type v) {
             return v.squaredNorm();
           };

  common::vector_type pos(2);

  pos << 3, 4;

  gsa::snapshot snap(f, pos);

  BOOST_CHECK_CLOSE( 3.0, snap.position()(0), 1e-10);
  BOOST_CHECK_CLOSE( 4.0, snap.position()(1), 1e-10);
  BOOST_CHECK_CLOSE(25.0, snap.fitness(), 1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
