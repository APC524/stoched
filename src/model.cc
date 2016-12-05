#include "model.h"

Model::Model(int n_vars,
             int n_events,
             Vector_xf (*rate_function) (double t, VectorXd state_array,
                                         VectorXd rate_params),
             Vector_xf (*event_function) (double t, VectorXd state_array,
                                          VectorXd event_params,
                                          int event_choice)
             ):
  n_vars(n_vars),
  n_events(n_events),
  (*rate_function)((*rate_function)),
  (*event_function)((*event_function))
{};

Model::~Model(){};
