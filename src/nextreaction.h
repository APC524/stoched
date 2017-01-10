/** 
 *  @file    nextreaction.h
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief   Class nextreaction implements Realization step() function
 *           using the exact Next Reaction algorithm of Gibson & Bruck
 *           (2000)
 *  
 */

#ifndef NEXTREACTION_H_
#define NEXTREACTION_H
#include "realization.h"
#include <float.h>

/**
 *  @brief Class NextReaction implements Realization step() function
 *           using the exact Next Reaction algorithm of Gibson & Bruck
 *           (2000) 
 */
class NextReaction : public Realization {
 public:
  // Default constructor for NextReaction
  NextReaction(Model *the_model, const Paramset & the_paramset,
               rng *the_rng, int n_vars, int n_events);
  
  // Destructor for NextReaction
  ~NextReaction();

  // Update waiting times
  int step();

  // Sets state_array and state_time to user-specified initial values
  int set_to_initial_state();
 private:
  double *waiting_times; ///< pause
};

#endif 
