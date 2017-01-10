/** 
 *  @file    realization_factory.cc
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Class RealizationFactory generates required instance of Realization 
 *         (FirstReaction, NextReaction, EulerLeap) based on input
 *  
 */

#include "realization_factory.h"

/**
 *   @brief  Create new realization 
 *   
 *   @param  the_model is a Model object
 *   @param  the_paramset is a Paramset object
 *   @param  the_rng is a random number generator 
 *   @param  n_vars is an int specifying variable count
 *   @param  n_events is an int specifying event count
 *
 *   @return nothing 
 */ 
Realization* RealizationFactory::NewRealization(Model *the_model,
						const Paramset & the_paramset,
						rng *the_rng,
						int n_vars,
						int n_events){
  int method = the_paramset.method;
  
  if(method == 0){
    return new FirstReaction(the_model, the_paramset, the_rng,
			     n_vars, n_events);
  };
  
  if(method == 1){
    return new NextReaction(the_model, the_paramset, the_rng,
			    n_vars, n_events);
  };

  if(method == 2) {
    return new EulerLeap(the_model, the_paramset, the_rng,
                         n_vars, n_events);
  };
  
  return NULL;

}
