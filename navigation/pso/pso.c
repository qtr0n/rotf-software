#include <time.h> 
#include <math.h> 
#include <float.h> 
#include <string.h> 
#include <stdio.h>
#include <gsl/gsl_rng.h>

#include "pso.h"

double roundNum (double d) {
  double g = 0.0, e = 0.0, f = 0.0;
  g = floor (d);
  e = d - g;
  if (d > 0){
    if (e > 0.5){
      f = g + 1;
    } else {
      f = g;
    }
  } else {
      if (e > 0.5) {
          f = g - 1;
      } else {
          f = g;
      }
  }
  return f;
}

int pso_calc_swarm_size(int dim) {
  int size = 10. + 2. * sqrt(dim);
  return (size > PSO_MAX_SIZE ? PSO_MAX_SIZE : size);
}

//Calculation of Inertial Weight
double calc_inertia_lin_dec(int step, pso_settings_t *settings) {
  int dec_stage = 3 * settings->steps / 4;
  if (step <= dec_stage)
    return settings->w_min + (settings->w_max - settings->w_min) *	\ (dec_stage - step) / dec_stage;
  else
    return settings->w_min;
}

// Global Neighbourhood Points
void inform_global(int *comm, double *pos_nb,
		   double *pos_b, double *fit_b,
		   double *gbest, int improved,
		   pso_settings_t *settings)
{
  int i;
  for (i=0; i<settings->size; i++)
    memmove((void *)&pos_nb[i*settings->dim], (void *)gbest,
            sizeof(double) * settings->dim);
}

void inform(int *comm, double *pos_nb, double *pos_b, double *fit_b,
	    int improved, pso_settings_t * settings)
{
  int i, j;
  int b_n; 
  for (j=0; j<settings->size; j++) {
    b_n = j; 
    for (i=0; i<settings->size; i++)
      if (comm[i*settings->size + j] && fit_b[i] < fit_b[b_n])
        b_n = i;
    memmove((void *)&pos_nb[j*settings->dim],
            (void *)&pos_b[b_n*settings->dim],
            sizeof(double) * settings->dim);
  }
}

// Ring Topology
void init_comm_ring(int *comm, pso_settings_t * settings) {
  int i;
  memset((void *)comm, 0, sizeof(int)*settings->size*settings->size);
  for (i=0; i<settings->size; i++) {
    comm[i*settings->size+i] = 1;
    if (i==0) {
      comm[i*settings->size+i+1] = 1;
      comm[(i+1)*settings->size-1] = 1;
    } else if (i==settings->size-1) {
      comm[i*settings->size] = 1;
      comm[i*settings->size+i-1] = 1;
    } else {
      comm[i*settings->size+i+1] = 1;
      comm[i*settings->size+i-1] = 1;
    }
  }
}

void inform_ring(int *comm, double *pos_nb,double *pos_b, double *fit_b,double *gbest, int improved,pso_settings_t * settings){
  inform(comm, pos_nb, pos_b, fit_b, improved, settings);
}

// Random Topology
void init_comm_random(int *comm, pso_settings_t * settings) {
  int i, j, k;
  memset((void *)comm, 0, sizeof(int)*settings->size*settings->size);
  for (i=0; i<settings->size; i++) {
    comm[i*settings->size + i] = 1;
    for (k=0; k<settings->nhood_size; k++) {
      j = gsl_rng_uniform_int(settings->rng, settings->size);
      comm[i*settings->size + j] = 1;
    }
  }
}

void inform_random(int *comm, double *pos_nb,double *pos_b, double *fit_b,double *gbest, int improved,pso_settings_t * settings){
  if (!improved)
    init_comm_random(comm, settings);
  inform(comm, pos_nb, pos_b, fit_b, improved, settings);
}

double ** pso_autofill_limits (double x_lo, double x_hi, int dim){
    double ** limits = (double **) malloc (sizeof (double *) * 2);
    limits[0] = (double *) malloc (sizeof (double) * dim);
    limits[1] = (double *) malloc (sizeof (double) * dim);
    int i = 0;
    for (i = 0; i < dim; i++) {
        limits[0][i] = x_lo;
        limits[1][i] = x_hi;
    }
    return limits;
}

void pso_print_limits (double ** limits, int dim){
    int i = 0;  
    for (i = 0; i < dim; i++) {
        printf ("x%d: lower = %f, higher = %f\n", i+1, limits[0][i], limits[1][i]);
    }
}

void pso_set_default_settings(pso_settings_t *settings) {
  settings->dim = 30;
  settings->x_lo = -20;
  settings->x_hi = 20;
  settings->goal = 1e-5;
  settings->limits = pso_autofill_limits (settings->x_lo, settings->x_hi, settings->dim);
  settings->size = pso_calc_swarm_size(settings->dim);
  settings->print_every = 10;
  settings->steps = 100000;
  settings->c1 = 1.496;
  settings->c2 = 1.496;
  settings->w_max = PSO_INERTIA;
  settings->w_min = 0.3;
  settings->numset = DECIMAL;
  settings->clamp_pos = 1;
  settings->nhood_strategy = PSO_NHOOD_RING;
  settings->nhood_size = 5;
  settings->w_strategy = PSO_W_LIN_DEC;
  settings->rng = NULL;
  settings->seed = time(0);
}


// Actual Particle Swarm Optimization Algorithm
void pso_solve(pso_obj_fun_t obj_fun, void *obj_fun_params,
	       pso_result_t *solution, pso_settings_t *settings)
{
  int free_rng = 0; 

  // Random Particles
  double pos[settings->size][settings->dim]; 
  double vel[settings->size][settings->dim]; 
  double pos_b[settings->size][settings->dim]; 
  double fit[settings->size]; 
  double fit_b[settings->size]; 

  // Swarm
  double pos_nb[settings->size][settings->dim]; 
  int comm[settings->size][settings->size]; 
  int improved; 

  int i, d, step;
  double a, b; 
  double rho1, rho2; 
  double w; 
  void (*inform_fun)(); 
  double (*calc_inertia_fun)(); 

  // Random Number Generator
  if (! settings->rng) {
    gsl_rng_env_setup();
    settings->rng = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(settings->rng, settings->seed);
    free_rng = 1;
  }

  switch (settings->nhood_strategy){
    case PSO_NHOOD_GLOBAL :
      inform_fun = inform_global;
      break;
    case PSO_NHOOD_RING :
      init_comm_ring((int *)comm, settings);
      inform_fun = inform_ring;
      break;
    case PSO_NHOOD_RANDOM :
      init_comm_random((int *)comm, settings);
      inform_fun = inform_random;
      break;
  }

  switch (settings->w_strategy){
    case PSO_W_LIN_DEC :
      calc_inertia_fun = calc_inertia_lin_dec;
      break;
  }


  solution->error = DBL_MAX;

// Swarm Initialization
  for (i=0; i<settings->size; i++) {
    for (d=0; d<settings->dim; d++) {
      a = gsl_rng_uniform_int (settings->rng, settings->limits[1][i]);
      b = gsl_rng_uniform_int (settings->rng, settings->limits[1][i]);
      pos[i][d] = a;
      pos_b[i][d] = a;
      vel[i][d] = (a-b) / 2.;
    }

    // Update the particle fitness
    fit[i] = obj_fun(pos[i], settings->dim, obj_fun_params);
    fit_b[i] = fit[i]; 
    if (fit[i] < solution->error) {
      solution->error = fit[i];
      memmove((void *)solution->gbest, (void *)&pos[i],sizeof(double) * settings->dim);
    }
  }

  // End 
  w = PSO_INERTIA;

  // Run Algorithm
  for (step=0; step<settings->steps; step++) {
    settings->step = step;
    if (settings->w_strategy)
      w = calc_inertia_fun(step, settings);
    if (solution->error <= settings->goal) {
      if (settings->print_every)
        printf("Goal achieved @ step %d (error=%.3e) :-)\n", step, solution->error);
      break;
  }

    inform_fun(comm, pos_nb, pos_b, fit_b, solution->gbest,improved, settings);
    improved = 0;
    for (i=0; i<settings->size; i++) {
      for (d=0; d<settings->dim; d++) {
        rho1 = settings->c1 * gsl_rng_uniform(settings->rng);
        rho2 = settings->c2 * gsl_rng_uniform(settings->rng);
        
	// Update Velocity
        vel[i][d] = w * vel[i][d] +	\
          rho1 * (pos_b[i][d] - pos[i][d]) +	\
          rho2 * (pos_nb[i][d] - pos[i][d]);

  // Update Position
        pos[i][d] += vel[i][d];
        if (settings->numset == INTEGER){
            pos[i][d] = roundNum (pos[i][d]);
        }

        if (settings->clamp_pos) {
          if (pos[i][d] < settings->limits[0][i]) {
            pos[i][d] = settings->limits[0][i];
            vel[i][d] = 0;
          } else if (pos[i][d] > settings->limits[1][i]) {
            pos[i][d] = settings->limits[1][i];
            vel[i][d] = 0;
          }
        } else {
          if (pos[i][d] < settings->limits[0][i]) {
            pos[i][d] = settings->limits[1][i] - fmod(settings->limits[0][i] - pos[i][d],settings->limits[1][i] - settings->limits[0][i]);
            vel[i][d] = 0;
          } 
          else if (pos[i][d] > settings->limits[1][i]) {
            pos[i][d] = settings->limits[0][i] + fmod(pos[i][d] - settings->limits[1][i],settings->limits[1][i] - settings->limits[0][i]);
            vel[i][d] = 0;
          }
        }
      }

      fit[i] = obj_fun(pos[i], settings->dim, obj_fun_params);
      if (fit[i] < fit_b[i]) {
        fit_b[i] = fit[i];
        memmove((void *)&pos_b[i], (void *)&pos[i],sizeof(double) * settings->dim);
      }
      
      if (fit[i] < solution->error) {
        improved = 1;
        solution->error = fit[i];
        memmove((void *)solution->gbest, (void *)&pos[i],sizeof(double) * settings->dim);
      }
    }

    if (settings->print_every && (step % settings->print_every == 0))
      printf("Step %d (w=%.2f) :: min err=%.5e\n", step, w, solution->error);
  }

  if (free_rng)
    gsl_rng_free(settings->rng);
}