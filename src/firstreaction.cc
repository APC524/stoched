#include "firstreaction.h"

FirstReaction::FirstReaction(Model *the_model, const Paramset & the_paramset, rng *the_rng, int n_vars, int n_events) :
  Realization(the_model, the_paramset, the_rng, n_vars, n_events)
{
  waiting_times = new double[n_events];
}

FirstReaction::~FirstReaction(){
  delete waiting_times;
}
 
int FirstReaction::step(){
  // update waiting times

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


