/** 
 *  @file    realization.h
 *  @author  Dylan Morris (peckham@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief APC 524, Final Project - Stoched 
 *
 *  @section DESCRIPTION
 *  
 */

#ifndef REALIZATION_H_
#define REALIZATION_H_
#include "../lib/eigen/Eigen/Core"
#include "../lib/eigen/Eigen/LU"
#include "model.h"
#include "paramset.h"

/**  
 *  @brief Class Realization holds realizations of a Model 
 *         (state array, propensities, waiting times, etc.) 
 */  
class Realization {
  using namespace Eigen;
 public:

  // Default constructor for Realization
  Realization(const Model & the_model, const Paramset & the_paramset);

  // Destructor of Realization
  ~Realization();

  const Model the_model;       ///< the_model is a Model instance
  const Paramset the_paramset; ///< the_paramset is a Paramset instance
  VectorXd state_array;        ///< state_array is a VectorXd specifiying variable values of a function
  VectorXd rates;              ///< rates is a VectorXd specifying variable values of a rate function
  double state_time;           ///< state_time is a double that tracks state progress

  // simulates the realization from t_inital to t_final
  int simulate();

  /// takes one simulation step according to the chosen algorithm 
  virtual int step();

  // prints the current state of the simulation
  int output_state();

  // sets state_array and state_time to their user-specified initial values
  int set_to_initial_state();
  
};

/**  
 *  @brief Class ExactRealization implements Realization step() function 
 *         using exact calculation
 */  
class ExactRealization : public Realization {
 public:
 
   //takes one simulation step according to the chosen algorithm 
  int step();
};

/**  
 *  @brief Class EulerLeapRealization implements Realization step() function 
 *         using Euler Leap method
 */  
class EulerLeapRealization : public Realization {
 public:

  //takes one simulation step according to the chosen algorithm 
  int step();
};

/**  
 *  @brief Class MidpointLeapRealization implements Realization step() function 
 *         using Midpoint Leap method
 */  
class MidpointLeapRealization : public Realization {
 public:

  //takes one simulation step according to the chosen algorithm 
  int step();
};

#endif
