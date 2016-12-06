#ifndef REALIZATION_H_
#define REALIZATION_H_
#include "../lib/eigen/Eigen/Core"
#include "../lib/eigen/Eigen/LU"
#include "model.h"
#include "paramset.h"


/* class to hold realizations of a model 
   (state array, propensities, waiting times, etc.) */

class Realization {
  using namespace Eigen;
 public:
  Realization(const Model & the_model, const Paramset & the_paramset);
  ~Realization();

  const Model the_model;
  const Paramset the_paramset;
  VectorXd state_array;
  VectorXd rates;
  double state_time;

  // simulates the realization from t_inital to t_final
  int simulate();

  /* takes one simulation step according to the chosen
   algorithm */
  virtual int step();

  // prints the current state of the simulation
  int output_state();

  /* sets state_array and state_time to 
     their user-specified initial values */
  int set_to_initial_state();
  

}

class ExactRealization : public Realization {
 public:
  int step();
}

class EulerLeapRealization : public Realization {
 public:
  int step();
}

class MidpointLeapRealization : public Realization {
 public:
  int step();
}

#endif