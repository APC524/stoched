#include <random>
#include "realization.h"
#include "xoroshiro128plus.h"
#include <math.h>
#include <stdio.h>
#include <float.h>

Realization::Realization(Model *the_model, const Paramset & the_paramset, rng *the_rng, int n_vars, int n_events) :
  the_model(the_model),
  the_paramset(the_paramset),
  the_rng(the_rng),
  n_vars(n_vars),
  n_events(n_events)
{
  state_array = new double[n_vars];
  rates = new double[n_events];
  set_to_initial_state();
}


Realization::~Realization(){
  delete state_array;
  delete rates;
}

int Realization::set_to_initial_state(){

  // check that the right number of inits have been supplied
  //assert(n_vars == the_paramset.n_vars);
  
  // create state_array and set to initial values
  for(int i = 0; i < n_vars; i++){
    state_array[i] = the_paramset.initial_values[i];
  }
  
  // set state_time to its initial value
  state_time = the_paramset.t_initial;

  // create rates array and set to initial rates
  the_model->updateRates(state_array, rates);

  return 0;
}


// simulates the realization from t_inital to t_final
int Realization::simulate(){
  double t_final = the_paramset.t_final;
  int max_iter = the_paramset.max_iter;
  
  bool time_stop = 0;
  bool max_iter_stop = 0;
  bool rate_stop = 0;
  int iter_count = 1;
  bool done = 0;

  set_to_initial_state();

  while(done==0){
    
    // take step according to method
    step();

    // output state of the simuation
    output_state();
    
    // increment iteration count
    iter_count++;

    /* check that stop conditions haven't been reached
       (maybe wrap this in a function) */ 
    if(state_time > t_final){
      time_stop = 1;
      done = 1;
    }
    else if (iter_count > max_iter) {
      max_iter_stop = 1;
      done = 1;
    }
    else if(rates_are_zero()){
      rate_stop = 1;
      done = 1;
    }
    else {}

  }

  
  return 0;
}

// prints the current state of the simulation
int Realization::output_state(){
  // to be modified depending on ultimately
  // chosen output format
  printf("%15.8f ", state_time);

  for(int i = 0; i < n_vars; i++){
    printf("%15.8f ", state_array[i]);
  }
  printf("\n");
  return 0;
}

bool Realization::rates_are_zero(){
  double total_rate = 0.0;
  for(int i = 0; i < n_events; i++){
    total_rate += rates[i];
  }
  return !(total_rate > DBL_MIN);
}


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
  for(int i = 0; i < n_events; i++){
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
