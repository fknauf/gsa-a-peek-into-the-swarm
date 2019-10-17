# Overview

This distribution consists of two programs that reproduce the results of the
paper titled "A Peek into the Swarm: Analysis of the Gravitational Search
Algorithm and Recommendations for Parameter Selection".

These programs are

* simulation
* swarmpositions

simulation reproduces the results in tables 1 through 3, writing them into
subdirectories under output/simulation. swarmpositions runs single simulations
with the parameters used to render figures 1 through 4 and prints the particle
positions after each iteration into files in a subdirectory under
output/swarmpositions.

Note that due to the stochastic nature of GSA, the results will vary slightly,
although the patterns described in the paper persist.

There are python scripts in output/swarmpositions that produce images like
figures 1 through 3. Figure 4 was rendered with gnuplot.

# Building

The build system is autoconf/automake, so the code can be built with

   ./configure
   make

The code depends on [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page).

# Running

After `make`,

   ./simulation

or

   ./swarmposition

# Rendering images

There are three scripts:

1. `plot_clouds.py` renders the full swarm into a contour plot for every step of
   optimization, as in figures 1 and 3.
2. `plot_step.py` renders sample particle trajectories during a single step as
   in figure 2 (center)
3. `plot_path.py` renders a sample trajectory over several steps as in figure 2
   (right)

These are invoked as

   ./plot_clouds.py <directory>          # e.g. ./plot_clouds.py rastrigin_20_20
   ./plot_step.py <directory>            # e.g. ./plot_step.py rastrigin_20_20
   ./plot_path.py <directory> <particle> # e.g. ./plot_path.py rastrigin_20_20 37

Files produced are

* `plot_clouds.py`: in `<directory>/gsa` files `positions.###.png`
* `plot_step.py`: in `<directory>/gsa` file `step20.png`
* `plot_path.py`: in `<directory>/gsa` file `path<particle>.png`

# Source code organization

The code falls, roughly speaking, into these subsets:

* src/gsa contains the implementation of GSA.
* src/random contains the implementation of random search used for comparison
  in figure 4.
* src/common contains utility classes that GSA shares with other optimization
  algorithms (that are not included here).
* src/testfunc.* and src/gsapaper.cc contain test functions.
* src/simulation.cc and src/indicators.hh for the simulation program
* src/swarmpositions.cc for the swarmpositions program

The implementation of GSA is structured as follows:

* search_parameters describes the selected parameter set, dimensionality of the problem,
  schedules for G and K as well as some features used in experiments unrelated to the paper
  (e.g. the disruptor class and pbest memory mechanic)
* snapshot is a tuple combining position and fitness value, used because those are always
  replaced in lockstep
* agent is a swarm particle
* stepper describes the swarm at a given time
* technique is a swarm factory

The simulation procedure is:

* A technique object describing the simulation is created
* In a loop (101/1001 times), a swarm stepper is created
* Each stepper is stepped T times, and every step relevant results are logged
