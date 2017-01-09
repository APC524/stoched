/* ------------- class Model -------------

   Header for class MODEL, which holds user-specified models 
   of stochastic systems from which realizations are to
   be simulated. A model may have variable parameters; 
   each complete set will be stored in an object of class
   Paramset

*/


#ifndef MODEL_H_
#define MODEL_H_
#include "../lib/eigen/Eigen/Core"
#include "../lib/eigen/Eigen/LU"



class Model {
  using namespace Eigen;

 public:
  Model(int n_vars,
        int n_events,
        VectorXd (*rate_function) (double t, VectorXd state_array,
                                    VectorXd rate_params),
        VectorXd (*event_function) (double t, VectorXd state_array,
                                     VectorXd event_params,
                                     int event_choice)
        );

  ~Model();

  const int n_vars;    // length of state array
  const int n_events;  // number of possible events

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
