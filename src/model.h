#ifndef MODEL_H_
#define MODEL_H_
#include <Eigen/Core>
#include <Eigen/LU>

using namespace Eigen;


/* class to hold user-specified models of stochastic systems
 so that realizations from them can be simulated */

class Model {
 public:
  Model(int n_vars, int n_events,
        Vector_xf (*rate_function) (double t, VectorXd state_array),
        Vector_xf (*event_function) (double t, VectorXd state_array,
                                     int event_choice));
  ~Model();

  const int n_vars;    // length of state array
  const int n_events;  // number of possible events

  /* pointer to function that calculates current rates 
     at which events occur */
  Vector_xf (*rate_function) (double t, VectorXd state_array);

  /* pointer to function that calculates change to state 
     array for a given event */
  Vector_xf (*event_function) (double t, VectorXd state_array,
                               int event_choice));
}

#endif
