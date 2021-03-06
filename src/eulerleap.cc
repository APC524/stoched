/** 
 *  @file    eulerleap.cc
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief  Class EulerLeap implements Realization step() function 
 *          using the basic tau leap approximate method of Gillepsie
 *          (2001). The method is analogous to the deterministic forward 
 *          Euler method for the numerical solution of ordinary
 *          differential equations.
 */

#include "eulerleap.h"
using namespace std;

/**
 *   @brief  Default constructor for EulerLeap
 *  
 *   @param  the_model is a Model object
 *   @param  the_paramset is a Paramset object
 *   @param  the_rng is a random number generator 
 *   @param  n_vars is an int specifying variable count
 *   @param  n_events is an int specifying event count
 * 
 *   @return nothing 
 */ 

EulerLeap::EulerLeap(Model *the_model, const Paramset & the_paramset,
                     rng *the_rng, int n_vars, int n_events) :
  Realization(the_model, the_paramset, the_rng, n_vars, n_events)
{
  // check for invalid tau leap simulation conditions
    if(!the_model->checkTauLeapAvail()) {
    throw runtime_error("Euler tau leap simulation can only be used "
                        "when events change state variables "
                        "by quantities that do not depend upon the "
                        "state variables themselves.\n\n"
                        "Example: \n "
                        "EVENT RATE \"a + b / 3\" \"a - 1\" \"b + 4\"\n"
                        "is a valid event for tau leap simulations.\n\n"
                        "EVENT RATE \"a + b / 3\" \"a - b\" \"b + 4\" \n"
                        "is not a valid event for tau leap simulations.\n");

      };
 
  if(the_paramset.timestep_size < 0){
    if(the_paramset.timestep_size == -2341.9382){
      throw runtime_error("No timestep size specified. "
                          "Tau leap methods require a "
                          "timestep size");
    }
    throw runtime_error("Invalid timestep size: timestep size must "
                        "be positive");
      };
}

/**
 *   @brief Destructor for MidpointLeap
 *  
 *   @return nothing 
 */ 

EulerLeap::~EulerLeap(){
}

/**
 *   @brief Sets state_array and state_time to their user-specified initial values
 *  
 *   @return int
 */ 

int EulerLeap::set_to_initial_state(){
  // call base method
  Realization::set_to_initial_state();

  return 0;
}

/**
 *   @brief Update waiting times
 *  
 *   @return int
 */  

int EulerLeap::step(){
  int n_occurences;
  /* do each event a number of
     times that is poisson distributed
     according to its rate */
  for(int event = 0; event < n_events; event++){
    n_occurences = the_rng->rpois(rates[event] *
                                  the_paramset.timestep_size);
    for(int k = 0; k < n_occurences; k++){
      the_model->updateState(event, state_array);
    };
  }
  
  // update time and then rates
  state_time += the_paramset.timestep_size;
  the_model->updateRates(state_array, rates);
  return 0;
}
