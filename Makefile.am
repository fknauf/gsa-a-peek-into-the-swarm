# gcc 5 with -std=c++11 complains about Eigen's use of std::bind1st, std::bind2nd,
# -Wno-deprecated-declarations makes it shut up

AM_CPPFLAGS = $$(pkg-config --cflags eigen3) -I$(top_srcdir)/src -Wno-deprecated-declarations -Wno-deprecated-copy
AM_CXXFLAGS = -Wall -Wextra -Wno-int-in-bool-context -pedantic -std=c++17
AM_LDLIBS   = -lm

EXTRA_DIST = \
  LICENSE \
  README.md \
  output/simulation/.dummy \
  output/swarmpositions/.dummy \
  output/swarmpositions/plot_clouds.py \
  output/swarmpositions/plot_path.py \
  output/swarmpositions/plot_step.py

bin_PROGRAMS = simulation swarmpositions 
check_PROGRAMS = test/test

TESTS = test/test

common     = \
  src/common/limits.cc \
  src/common/math.cc \
  src/common/random.cc \
  src/common/slide.cc \
  src/common/common.hh \
  src/common/types.hh \
  src/common/limits.hh \
  src/common/random.hh \
  src/common/math.hh \
  src/common/slide.hh

src_random = \
  src/random/agent.cc \
  src/random/search_parameters.cc \
  src/random/stepper.cc \
  src/random/technique.cc \
  src/random/random_search.hh \
  src/random/search_parameters.hh \
  src/random/types.hh \
  src/random/agent.hh \
  src/random/technique.hh \
  src/random/stepper.hh

src_gsa = \
  src/gsa/agent.cc \
  src/gsa/disruptor.cc \
  src/gsa/search_parameters.cc \
  src/gsa/stepper.cc \
  src/gsa/technique.cc \
  src/gsa/types.hh \
  src/gsa/search_parameters.hh \
  src/gsa/stepper.hh \
  src/gsa/technique.hh \
  src/gsa/gsa.hh \
  src/gsa/agent.hh \
  src/gsa/disruptor.hh \
  src/gsa/snapshot.hh

src_algorithms = \
  $(src_random) \
  $(src_gsa)

simulation_SOURCES = \
  src/simulation.cc \
  src/indicators.hh \
  src/testfunc.cc \
  src/testfunc.hh \
  src/gsapaper.cc \
  $(common) \
  $(src_algorithms)

swarmpositions_SOURCES = \
  src/swarmpositions.cc \
  src/testfunc.cc \
  src/testfunc.hh \
  src/gsapaper.cc \
  $(common) \
  $(src_algorithms)

test_test_SOURCES = \
  test/test_main.cc \
  test/group_limits.cc \
  test/group_math.cc \
  test/group_randomness.cc \
  test/group_slide.cc \
  test/group_gsa_search_parameters.cc \
  test/group_gsa_snapshot.cc \
  test/group_gsa_agent.cc \
  $(common) \
  $(src_algorithms)

test_test_CPPFLAGS = $(AM_CPPFLAGS) -D BOOST_TEST_DYN_LINK
test_test_CXXFLAGS = -g -O0
test_test_LDADD    = -lboost_unit_test_framework
