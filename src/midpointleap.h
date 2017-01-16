/** 
 *  @file    midpointleap.h
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    2016-01-16  
 *  @version 1.0 
 *  
 *  @brief  Class MidpointLeap implements Realization step() function 
 *          using the midpoint tau leap approximate algorithm of Gillepsie
 *          (2001). The method is analogous to the deterministic midpoint 
 *          (2nd-order Runge-Kutta) method for the numerical solution of 
 *          ordinary differential equations.
 *  
 */

#ifndef MIDPOINTLEAP_H_
#define MIDPOINTLEAP_H_
#include <stdexcept>  

#include "realization.h"

/**  
 *  @brief  Class MidpointLeap implements Realization step() function 
 *          using the midpoint tau leap approximate algorithm of Gillepsie
 *          (2001). The method is analogous to the deterministic midpoint 
 *          (2nd-order Runge-Kutta) method for the numerical solution of 
 *          ordinary differential equations.
 */  
class MidpointLeap : public Realization {
 public:
  // Default constructor for MidpointLeap
  MidpointLeap(Model *the_model, const Paramset & the_paramset,
               rng *the_rng, int n_vars, int n_events);
  // Destructor for MidpointLeap
  ~MidpointLeap();

  // take one simulation step using MidpointLeap 
  int step();
  
  // set state_array and state_time to user-specified initial values
  int set_to_initial_state();

 private:
  double *midpoint_array_; ///< midpoint_array_ is a double array holding the current midpoints for the tau-leap step
};

#endif 
