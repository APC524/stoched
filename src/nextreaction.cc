/** 
 *  @file    nextreaction.cc
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief   Inherit Realization class for next reaction instance
 *  
 */


#include "nextreaction.h"

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

NextReaction::NextReaction(Model *the_model, const Paramset & the_paramset, rng *the_rng, int n_vars, int n_events) :
  Realization(the_model, the_paramset, the_rng, n_vars, n_events)
{
  waiting_times = new double[n_events];
}

/**
 *   @brief Destructor for NextReaction
 *  
 *   @return nothing 
 */ 
NextReaction::~NextReaction(){
  delete waiting_times;
}

/**
 *   @brief Sets state_array and state_time to their user-specified initial values
 *  
 *   @return int
 */ 
int NextReaction::set_to_initial_state(){
  // call base method
  Realization::set_to_initial_state();

  // initialize waiting times
  for(int i = 0; i < n_events; i++){
    waiting_times[i] = the_rng->rexp(rates[i]);
  }

  return 0;
}


/**
 *   @brief Update waiting times
 *  
 *   @return int
 */  
int NextReaction::step(){
  // find the next rxn
  int min_ind = 0;
  for(int i = 0; i < n_events; i++){
    if(waiting_times[i] < waiting_times[min_ind]){
      min_ind = i;
    }
  }
  double delta_t = waiting_times[min_ind];
  
  // update time, do event, update rates
  state_time += delta_t;
  the_model->updateState(min_ind, state_array);
  
  /* calculate new rates and waiting times from old ones,
   while also updating rates array */
  double newrate;
  for(int i = 0; i < n_events; i++){
    newrate = the_model->getEventRate(i, state_array);
    if(rates[i] > DBL_MIN){
      waiting_times[i] = (rates[i]/newrate) *
        (waiting_times[i] - delta_t);
    }
    else if(newrate > DBL_MIN){
      waiting_times[i] = the_rng->rexp(newrate);
    }
    
    // update rates[i] 
    rates[i] = newrate;

  }

  // draw a new waiting time for event that just happened
  waiting_times[min_ind] = the_rng->rexp(rates[min_ind]);
  
  return 0;
}
