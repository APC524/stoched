#ifndef PARAMSET_H_
#define PARAMSET_H_

/* class to hold a particular set of pameters for 
   user requested simulation run(s) */

class Paramset {
 public:
  Paramset(int method,
           int n_vars,
           double *initial_values,
           double t_initial,
           double t_final,
           double timestep_size,
           int n_realizations,
           int max_iter,
           int seed);
  ~Paramset();

  const int method;              // which algorithm to use for simulation
  const int n_vars;              // number of initial values/variables
  const double *initial_values;  // initial values for variables
  const double t_initial;        // initial time for simulation
  const double t_final;          // final time for simulation
  
  const double timestep_size;    // size of timestep for approximate
                                 // ("tau leap") methods

  int n_realizations;            // number of realizations to simulate
                                 // for this parameter set
  
  int max_iter;                  // max number of iterations to simulate
  int seed;                      // seed for the random number generator

};


#endif
