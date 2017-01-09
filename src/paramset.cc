/** 
 *  @file    paramset.cc
 *  @author  Dillon 
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief APC 524, Final Project - Stoched 
 *
 *  @section DESCRIPTION
 *  
 */

#include "paramset.h"

using namespace Eigen;

/**
 * @brief Default constructor for Paramset
 *
 * @param method is an int that specifies algorithm to use for simulation
 * @param rate_params is a VectorXd that specifies parameters for rate function
 * @param event_params is a VectorXd that specifies parameters for event function
 * @param initial_values is a VectorXd that sets initial values for variables
 * @param t_initial is a double that sets initial time for simulation
 * @param t_final is a double that sets initial time for simulation
 * @param timestep_size is a double representing the size of the timestep for approximate methods
 * @param n_realizations is an int representing number of realizations to simulate
 * @param max_iter is an int and is the maximum number of iterations to simulate
 */

Paramset::Paramset(int method,
                   int n_vars,
                   double *initial_values,
                   double t_initial,
                   double t_final,
                   double timestep_size,
                   int n_realizations,
                   int max_iter,
                   int seed) :
  
  method(method),                 // which algorithm to use for simulation
  n_vars(n_vars),                 // number of variables 
  initial_values(initial_values), // initial values for variables
  t_initial(t_initial),           // initial time for simulation
  t_final(t_final),               // final time for simulation
  timestep_size(timestep_size),   // size of timestep for approximate methods
  n_realizations(n_realizations), // number of realizations to simulate
  max_iter(max_iter),             // max number of iterations to simulate
  seed(seed)                      // seed for the random number generator
{};

Paramset::~Paramset(){};

