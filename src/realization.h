#ifndef REALIZATION_H_
#define REALIZATION_H_
#include "model.h"
#include "paramset.h"
#include "rng.h"


/* class to hold realizations of a model 
   (state array, propensities, waiting times, etc.) */

class Realization {
 public:
  Realization(Model *the_model, const Paramset & the_paramset,
              rng *the_rng, int n_vars, int n_events);
  virtual ~Realization();

  Model *the_model;
  const Paramset the_paramset;
  rng *the_rng;
  const int n_vars;
  const int n_events;
  double *state_array;
  double *rates;
  double state_time;

  // simulates the realization from t_inital to t_final
  int simulate();

  /* takes one simulation step according to the chosen
   algorithm */
  virtual int step() = 0;

  // checks whether all rates are zero
  bool rates_are_zero();
  
  // prints the current state of the simulation
  int output_state();

  /* sets state_array and state_time to 
     their user-specified initial values */
  int set_to_initial_state();  

};

class DirectMethod : public Realization {
 public:
  DirectMethod(Model *the_model, const Paramset & the_paramset,
               rng *the_rng, int n_vars, int n_events);
  ~DirectMethod();
  int step();
 private:
  double *waiting_times;
};

class EulerLeap : public Realization {
 public:
  int step();
};

class MidpointLeap : public Realization {
 public:
  int step();
};

#endif
