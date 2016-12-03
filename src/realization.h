#ifndef REALIZATION_H_
#define REALIZATION_H_
#include <Eigen/Core>
#include <Eigen/LU>
#include "model.h"
#include "paramset.h"

using namespace Eigen;


/* class to hold realizations of a model 
   (state array, propensities, waiting times, etc.) */

class Realization {
 public:
  Realization(const Model & the_model, double t_initial,
              double t_final, int max_iter);
  ~Realization();

  Model the_model;
  VectorXd state_array;
  VectorXd waiting_times;
  double state_time;

  // simulates the realization from t_inital to t_final
  int simulate();

  /* takes one simulation step according to the chosen
   algorithm */
  virtual int step();

  // prints the current state of the simulation
  int output_state();

 private:
  const double t_inital;
  const double t_final;
  const int max_iter;

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
