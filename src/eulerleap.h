/** 
 *  @file    eulerleap.h
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief  Class EulerLeap implements Realization step() function 
 *          using Euler Leap method
 *  
 */

#ifndef EULERLEAP_H_
#define EULERLEAP_H_
#include "realization.h"
#include <stdexcept>  

/**  
 *  @brief Class EulerLeap implements Realization step() function 
 *         using Euler Leap method
 */  
class EulerLeap : public Realization {
 public:
  // Default constructor for EulerLeap
  EulerLeap(Model *the_model, const Paramset & the_paramset,
               rng *the_rng, int n_vars, int n_events);
  // Destructor for EulerLeap
  ~EulerLeap();

  // takes one simulation step using EulerLeap 
  int step();
  
  // set state_array and state_time to user-specified initial values
  int set_to_initial_state();
};

#endif 
