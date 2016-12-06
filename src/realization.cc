#include <random>
#include "realization.h"
#include "xoroshiro128plus.h"
#include <math.h>
#include <stdio.h>

Realization::Realization(const Model & the_model, const Paramset & the_paramset, const rng & the_rng) :
  the_model(the_model),
  the_paramset(the_paramset),
  the_rng(the_rng),
  n_vars(the_model.n_vars),
  n_events(the_model.n_events)
{
  set_to_initial_state();
}


virtual Realization::~Realization(){
  delete state_array;
  delete rates;
}


int Realization::set_to_initial_state(){

  // check that the right number of inits have been supplied
  assert(n_vars == the_paramset.n_vars);
  
  // create state_array and set to initial values
  state_array = new double[n_vars];
  for(int i = 0; i < n_vars; i++){
    state_array[i] = the_paramset.initial_values[i];
  }
  
  // set state_time to its initial value
  state_time = the_paramset.t_initial;

  // create rates array and set to initial rates
  rates = new double[n_events]
  the_model.updateRates(rates)

  return 0;
}

// gets rates from the model for all events


// simulates the realization from t_inital to t_final
Realization::simulate(){
  t_initial = the_paramset.t_initial;
  t_final = the_paramset.t_final;
  
  bool time_stop = 0;
  bool max_iter_stop = 0;
  bool rate_stop = 0;
  int iter_count=1;
  bool done = 0;

  // add logic here to check that all conditions below are met initially
  rates = the_model.updateRates(rates)

  while(done==0){

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
    else if(rates.isZero(0)){
      rate_stop = 1;
      done = 1;
    }
    else {}
    
    // take step according to method
    step();

    // output state of the simuation
    output_state();
    
    // update rates and increment iteration count
    the_model.updateRates(rates);
    iter_count++;
  }
}

// prints the current state of the simulation
Realization::output_state(){
  // to be modified depending on ultimately
  // chosen output format
  printf("%15.8f", state_time);

  for(int = 0; i < n_vars; i++){
    printf("%15.8f", state_array[i])
  }

}


DirectMethod::DirectMethod(const Model & the_model, const Paramset & the_paramset) :
  Realization(the_model, the_paramset)
{
  waiting_times = new double[n_events];
}}

DirectMethod::~DirectMethod(){
  delete waiting_times;
}

DirectMethod::step(){
  for(int i = 0; i < n_vars; i++){
    waiting_times[i] = the_rng.rexp(rates[i]);
  }
  std::cout << waiting_times;
}
