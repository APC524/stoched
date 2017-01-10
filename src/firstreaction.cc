/** 
 *  @file    firstreaction.cc
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief   Inherit Realization class for first reaction instance
 *  
 */

#include "firstreaction.h"

/**
 *   @brief  Default constructor for NextReaction
 *  
 *   @param  the_model is a Model object
 *   @param  the_paramset is a Paramset object
 *   @param  the_rng is a random number generator 
 *   @param  n_vars is an int specifying variable count
 *   @param  n_events is an int specifying event count
 * 
 *   @return nothing 
 */ 
FirstReaction::FirstReaction(Model *the_model, const Paramset & the_paramset, rng *the_rng, int n_vars, int n_events) :
  Realization(the_model, the_paramset, the_rng, n_vars, n_events)
{
  waiting_times = new double[n_events];
}

/**
 *   @brief Destructor for FirstReaction
 *  
 *   @return nothing 
 */ 
FirstReaction::~FirstReaction(){
  delete waiting_times;
}


/**
 *   @brief Update waiting times
 *  
 *   @return int
 */  
int FirstReaction::step(){

  int min_ind = 0;
  int i;
  for(i = 0; i < n_events; i++){
    waiting_times[i] = the_rng->rexp(rates[i]);
    if(waiting_times[i] < waiting_times[min_ind]){
      min_ind = i;
    }
  }

  // update time, do event, update rates
  state_time += waiting_times[min_ind];
  the_model->updateState(min_ind, state_array);
  the_model->updateRates(state_array, rates);

  return 0;
}

