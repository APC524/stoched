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
 * @param
 * @param
 * @param
 * @param
 *
 */

Paramset::Paramset(int method,
                   VectorXd rate_params,
                   VectorXd event_params,
                   VectorXd initial_values,
                   double t_initial,
                   double t_final,
                   double timestep_size,
                   int n_realizations,
                   int max_iter) :
  
  method(method),                 //  which algorithm to use for simulation
  rate_params(rate_params),       //  parameters for rate function
  event_params(event_params),     //  parameters for event function
  initial_values(initial_values), //  initial values for variables
  t_initial(t_initial),           //  initial time for simulation
  t_final(t_final),               //  final time for simulation
  timestep_size(timestep_size),   //  size of timestep for approximate methods
  n_realizations(n_realizations), //  number of realizations to simulate
  max_iter(max_iter)              //  max number of iterations to simulate
{};

Paramset::~Paramset();

