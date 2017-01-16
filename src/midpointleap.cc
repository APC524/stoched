/** 
 *  @file    midpointleap.cc
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

#include "midpointleap.h"
using namespace std;

MidpointLeap::MidpointLeap(Model *the_model, const Paramset & the_paramset,
                     rng *the_rng, int n_vars, int n_events) :
  Realization(the_model, the_paramset, the_rng, n_vars, n_events)
{
  // check for invalid tau leap simulation conditions
    if(!the_model->checkTauLeapAvail()) {
    throw runtime_error("Midpoint tau leap simulation can only be used "
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

  /// intialize midpoint array
  midpoint_array_ = new double[n_vars];
  
  for(int i = 0; i < n_vars; i++){
    midpoint_array_[i] = 0;
  }
}


MidpointLeap::~MidpointLeap(){
  delete midpoint_array_;
}

int MidpointLeap::set_to_initial_state(){
  // call base method
  Realization::set_to_initial_state();

  return 0;
}


int MidpointLeap::step(){

  // populate midpoint array with current midpoints for each variable
  for(int ivar = 0; ivar < n_vars; ivar++){
    midpoint_array_[ivar] = state_array[ivar]
      + 0.5 * the_paramset.timestep_size *
      the_model->getContDeriv(ivar, state_array);
  }

  // get event rates from midpoints
  the_model->updateRates(midpoint_array_, rates);
  
  int n_occurences;
  /* do each event a number of
     times that is poisson distributed
     according to its midpoint-determined rate */  
  
  for(int event = 0; event < n_events; event++){
    n_occurences = the_rng->rpois(rates[event] *
                                  the_paramset.timestep_size);
    for(int k = 0; k < n_occurences; k++){
      the_model->updateState(event, state_array);
    };
  }
  
  // update time and then rates
  state_time += the_paramset.timestep_size;
  return 0;
}
