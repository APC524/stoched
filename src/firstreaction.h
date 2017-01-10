/** 
 *  @file    firstreaction.h
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief   Class FirstReaction implements Realization step() function
 *           using the exact First Reaction algorithm of Gillespie (1971)
 */

#ifndef FIRSTREACTION_H_
#define FIRSTREACTION_H_
#include "realization.h"

/**
 *  @brief Class FirstReaction implements Realization step() function
 *           using the exact First Reaction algorithm of Gillespie (1971)
 */
class FirstReaction : public Realization {
 public:
  // Default constructor for FirstReaction
  FirstReaction(Model *the_model, const Paramset & the_paramset,
               rng *the_rng, int n_vars, int n_events);
  
  // Destructor for FirstReaction
  ~FirstReaction();

  // Update waiting times
  int step();
 private:
  double *waiting_times;  ///< pause
};

#endif
