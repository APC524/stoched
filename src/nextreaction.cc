#include "nextreaction.h"

NextReaction::NextReaction(Model *the_model, const Paramset & the_paramset, rng *the_rng, int n_vars, int n_events) :
  Realization(the_model, the_paramset, the_rng, n_vars, n_events)
{
  waiting_times = new double[n_events];
}

NextReaction::~NextReaction(){
  delete waiting_times;
}

int NextReaction::set_to_initial_state(){
  // call base method
  Realization::set_to_initial_state();

  // initialize waiting times
  for(int i = 0; i < n_events; i++){
    waiting_times[i] = the_rng->rexp(rates[i]);
  }

  return 0;
}


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
