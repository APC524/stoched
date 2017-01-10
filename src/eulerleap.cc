/** 
 *  @file    eulerleap.cc
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief  Class EulerLeap implements Realization step() function 
 *          using Euler Leap method
 *  
 */

#include "eulerleap.h"
using namespace std;

EulerLeap::EulerLeap(Model *the_model, const Paramset & the_paramset,
                     rng *the_rng, int n_vars, int n_events) :
  Realization(the_model, the_paramset, the_rng, n_vars, n_events)
{
  // check for invalid tau leap simulation conditions
  
  // uncomment model flag check below once implemented by Kevin
  /*
  if(!the_model->tau_leap_available) {
    throw runtime_error("Euler tau leap simulation can only be used "
                        "when all possible events change variables "
                        "by an quantity that does not depend upon the "
                        "current values of the state variables \n\n"
                        "Example: \n "
                        "EVENT RATE \"a + b / 3\" \"a - 1\" \"b + 4\"\n\n"
                        "is a valid event for tau leap simulations.\n\n"
                        "EVENT RATE \"a + b / 3\" \"a - b\" \"b + 4\" \n"
                        "is not a valid event for tau leap simulations.");

      };
  */
  if(the_paramset.timestep_size < 0){
    throw runtime_error("Invalid timestep size: timestep size must "
                        "be positive");
      };
}

EulerLeap::~EulerLeap(){
}

int EulerLeap::set_to_initial_state(){
  // call base method
  Realization::set_to_initial_state();

  return 0;
}


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
