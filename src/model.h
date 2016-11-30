#ifndef MODEL_H_
#define MODEL_H_
#include <Eigen/Core>
#include <Eigen/LU>

using namespace Eigen;

class Model {
 public:
  Model(int n_vars, int n_events,
        Vector_xf (*rate_function) (double t, VectorXd state_array),
        Vector_xf (*event_function) (double t, VectorXd state_array,
                                     int event_choice));
  ~Model();

  const int n_vars;
  const int n_events;

  Vector_xf (*rate_function) (double t, VectorXd state_array);
  Vector_xf (*event_function) (double t, VectorXd state_array,
                               int event_choice));
}

#endif
