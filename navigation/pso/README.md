# Particle Swarm Optimization(PSO)

## Logic:
PSO is a computational method that optimizes a problem by iteratively trying to improve a candidate solution with regard to a given measure of quality. It consists of two main components:

### Neighbourhood Topologies: 
Weights are given to each of the 3 topologies, namely Global, Ring and [Random Topology](http://clerc.maurice.free.fr/pso/random_topology.pdf) which are used to find the next particle i.e velocity and position estimate.

### Inertial Weight Strategies:
Value of this weight determines the balance between global and local search using either Constant Value Approach or Linearly increasing weightage approach.

## Code:
* pso.c: Actual Algorithm based on kkentzo's [PSO Library](https://github.com/kkentzo/pso).
* pathplanning.c: Takes input [maps](https://github.com/theobscuredev/rotf-software/tree/main/navigation/pso/Trials) and contains the functions for working with the input. Map is a 2D grid of binary values.
* execPSO.sh: Bash file to run the MATLAB Scripts.
