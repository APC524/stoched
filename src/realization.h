/** 
 *  @file    realization.h
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Class Realization holds realizations of a Model 
 *         (state array, propensities, waiting times, etc.) 
 *
 *
 */

#ifndef REALIZATION_H_
#define REALIZATION_H_

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <float.h>

#include "model.h"
#include "paramset.h"
#include "rng.h"


/**  
 *  @brief Class Realization holds realizations of a Model 
 *         (state array, propensities, waiting times, etc.) 
 */  

class Realization {
 public:

  // Default constructor for Realization
  Realization(Model *the_model, const Paramset & the_paramset,
              rng *the_rng, int n_vars, int n_events);

  // Destructor of Realization
  virtual ~Realization();

  Model *the_model;             ///< the_model is a Model instance
  const Paramset the_paramset;  ///< the_paramset is a Paramset instance
  rng *the_rng;                 ///< the_rng is an random number generator
  const int n_vars;             ///< n_vars is an int specifying number of variables
  const int n_events;           ///< n_events is an int specifying number of events
  double *state_array;          ///< state_array is a double array specifiying variable values of a function
  double *rates;                ///< rates is a double array specifying variable values of a rate function
  double state_time;            ///< state_time is a double that tracks state progress

  // simulates the realization from t_inital to t_final
  int simulate(std::ofstream& myfile);

  /// takes one simulation step according to the chosen algorithm 
  virtual int step() = 0;

  // checks whether all rates are zero
  bool rates_are_zero();
  
  // prints the current state of the simulation
  int output_state(std::ofstream& myfile);

  /* sets state_array and state_time to 
     their user-specified initial values 
     and possibly does other setup logic 
     in derived classes */
  virtual int set_to_initial_state();
  
};

#endif
