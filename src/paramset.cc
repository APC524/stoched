#include "paramset.h"

Paramset::Paramset(int method,
                   int n_vars,
                   double *initial_values,
                   double t_initial,
                   double t_final,
                   double timestep_size,
                   int n_realizations,
                   int max_iter,
                   int seed) :
  
  method(method),                 // which algorithm to use for simulation
  n_vars(n_vars),                 // number of variables 
  initial_values(initial_values), // initial values for variables
  t_initial(t_initial),           // initial time for simulation
  t_final(t_final),               // final time for simulation
  timestep_size(timestep_size),   // size of timestep for approximate methods
  n_realizations(n_realizations), // number of realizations to simulate
  max_iter(max_iter),             // max number of iterations to simulate
  seed(seed)                      // seed for the random number generator
{};

Paramset::~Paramset(){};

