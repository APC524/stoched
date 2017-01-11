/** 
 *  @file    eulerleap.h
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief  Class EulerLeap implements Realization step() function 
 *          using the basic tau leap approximate algorithm of Gillepsie
 *          (2001). The method is analogous to the deterministic forward 
 *          Euler method the numerical solution of ordinary
 *          differential equations.
 *  
 */

#ifndef EULERLEAP_H_
#define EULERLEAP_H_
#include <stdexcept>  

#include "realization.h"

/**  
 *  @brief Class EulerLeap implements Realization step() function 
 *          using the basic tau leap approximate algorithm of Gillepsie
 *          (2001). The method is analogous to the deterministic forward 
 *          Euler method the numerical solution of ordinary
 *          differential equations.
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
