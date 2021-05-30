#include <stdio.h>
#include <math.h>

#ifndef PSO_H_
#define PSO_H_

// Maximum Swarm Size
#define PSO_MAX_SIZE 100 
#define PSO_INERTIA 0.7298 

// Neighbour Hood Schemes

// Global best topology
#define PSO_NHOOD_GLOBAL 0

// Ring topology
#define PSO_NHOOD_RING 1

// Random neighborhood topology
#define PSO_NHOOD_RANDOM 2

// Inertia Weight Update Functions
#define PSO_W_CONST 0
#define PSO_W_LIN_DEC 1

// Discretization Flags
#define INTEGER 0
#define DECIMAL 1

typedef struct {
  double error;
  double *gbest; 
} 

pso_result_t;

// Objective Function Type
typedef double (*pso_obj_fun_t)(double *, int, void *);

// PSO Settings
typedef struct {
  int dim; 
  double x_lo; 
  double x_hi; 
  double goal; 
  double ** limits; 

  int size; 
  int print_every; 
  int steps; // maximum number of iterations
  int step; // current PSO step
  double c1; // cognitive coefficient
  double c2; // social coefficient
  double w_max; // max inertia weight value
  double w_min; // min inertia weight value

  int numset; // Set of numbers to use as X values. Default = DECIMAL. 

  int clamp_pos; // whether to keep particle position within defined bounds (TRUE)
  // or apply periodic boundary conditions (FALSE)
  int nhood_strategy; // neighborhood strategy (see PSO_NHOOD_*)
  int nhood_size; // neighborhood size
  int w_strategy; // inertia weight strategy (see PSO_W_*)

  void *rng; // pointer to random number generator (use NULL to create a new RNG)
  long seed; // seed for the generator
  
} pso_settings_t;


// set x value limits using two constants
double ** pso_autofill_limits (double x_lo, double x_hi, int dim);
// print those limits
void pso_print_limits (double ** limits, int dim);

// return the swarm size based on dimensionality
int pso_calc_swarm_size(int dim);

// set the default PSO settings
void pso_set_default_settings(pso_settings_t *settings);

// minimize the provided obj_fun using PSO with the specified settings
// and store the result in *solution
void pso_solve(pso_obj_fun_t obj_fun, void *obj_fun_params,pso_result_t *solution, pso_settings_t *settings);

#endif 