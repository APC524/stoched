#ifndef MODEL_H_
#define MODEL_H_
#include <Eigen/Core>
#include <Eigen/LU>

using namespace Eigen;


/* class to hold user-specified models of stochastic systems
 so that realizations from them can be simulated */

class Model {
 public:
  Model(int n_vars,
        int n_events,
        int method, 
        Vector_xf (*rate_function) (double t, VectorXd state_array,
                                    VectorXd rate_params),
        Vector_xf (*event_function) (double t, VectorXd state_array,
                                     VectorXd event_params,
                                     int event_choice)
        );

  ~Model();

  const int n_vars;    // length of state array
  const int n_events;  // number of possible events
  const int method;    // which algorithm to use for simulation

  /* pointer to function that calculates current rates 
     at which events occur */
  Vector_xf (*rate_function) (double t, VectorXd state_array,
                              VectorXd rate_params);

  /* pointer to function that calculates change to state 
     array for a given event */
  Vector_xf (*event_function) (double t, VectorXd state_array,
                               VectorXd event_params,
                               int event_choice));
}

#endif
