#include <gsa/agent.hh>

#include <boost/test/unit_test.hpp>
#include <random>

BOOST_AUTO_TEST_SUITE( ts_gsa_agent )

BOOST_AUTO_TEST_CASE( basic )  {
  auto f = [](common::vector_type v) {
             return v.squaredNorm();
           };

  std::vector<gsa::agent> pop;

  common::vector_type vel(2);
  common::vector_type pos(2);

  pos << 3, 4;
  vel << 0, 0;
  pop.emplace_back(gsa::agent(f, pos, vel, false));

  pos << -2, 3;
  vel <<  2, 2;
  pop.emplace_back(gsa::agent(f, pos, vel, false));

  pos <<  1, 2;
  vel << -1, 1;
  pop.emplace_back(gsa::agent(f, pos, vel, false));

  BOOST_CHECK_CLOSE(25.0, pop[0].fitness(), 1e-10);
  BOOST_CHECK_CLOSE(13.0, pop[1].fitness(), 1e-10);
  BOOST_CHECK_CLOSE( 5.0, pop[2].fitness(), 1e-10);

  for(auto &a : pop) {
    a.update_mass_pass1(5.0, 25.0);
  }

  BOOST_CHECK_SMALL(     pop[0].mass(), 1e-10);
  BOOST_CHECK_CLOSE(0.6, pop[1].mass(), 1e-10);
  BOOST_CHECK_CLOSE(1.0, pop[2].mass(), 1e-10);

  for(auto &a : pop) {
    a.update_mass_pass2(1.6);
  }

  BOOST_CHECK_SMALL(           pop[0].mass(), 1e-10);
  BOOST_CHECK_CLOSE(0.6 / 1.6, pop[1].mass(), 1e-10);
  BOOST_CHECK_CLOSE(1.0 / 1.6, pop[2].mass(), 1e-10);
}

BOOST_AUTO_TEST_SUITE_END()
