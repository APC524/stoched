#include "paramset.h"

using namespace Eigen;

Paramset::Paramset(int method,
                   VectorXd rate_params,
                   VectorXd event_params,
                   VectorXd initial_values,
                   double t_initial,
                   double t_final,
                   double timestep_size,
                   int n_realizations,
                   int max_iter,
                   int seed) :
  
  method(method),                 // which algorithm to use for simulation
  rate_params(rate_params),       // parameters for rate function
  event_params(event_params),     // parameters for event function
  initial_values(initial_values), // initial values for variables
  t_initial(t_initial),           // initial time for simulation
  t_final(t_final),               // final time for simulation
  timestep_size(timestep_size),   // size of timestep for approximate methods
  n_realizations(n_realizations), // number of realizations to simulate
  max_iter(max_iter),             // max number of iterations to simulate
  seed(seed)                      // seed for the random number generator
{};

Paramset::~Paramset();

