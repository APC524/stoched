#include <random>
#include "realization.h"
#include "xoroshiro128plus.h"
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>


Realization::Realization(Model *the_model, const Paramset & the_paramset, rng *the_rng, int n_vars, int n_events) :
  the_model(the_model),
  the_paramset(the_paramset),
  the_rng(the_rng),
  n_vars(n_vars),
  n_events(n_events)
{
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
  state_array = new double[n_vars];
  for(int i = 0; i < n_vars; i++){
    state_array[i] = the_paramset.initial_values[i];
  }
  
  // set state_time to its initial value
  state_time = the_paramset.t_initial;

  // create rates array and set to initial rates
  rates = new double[n_events];
  the_model->updateRates(state_array, rates);

  return 0;
}


// simulates the realization from t_inital to t_final
int Realization::simulate(std::ofstream& myfile){
  double t_initial = the_paramset.t_initial;
  double t_final = the_paramset.t_final;
  int max_iter = the_paramset.max_iter;
  
  bool time_stop = 0;
  bool max_iter_stop = 0;
  bool rate_stop = 0;
  int iter_count = 1;
  bool done = 0;

  // add logic here to check that all conditions below are met initially
  the_model->updateRates(state_array, rates);

  while(done==0){
    
    // take step according to method
    step();

    // output state of the simuation
    output_state(myfile);
    
    // update rates and increment iteration count
    the_model->updateRates(state_array, rates);
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
int Realization::output_state(std::ofstream& myfile){
  // to be modified depending on ultimately
  // chosen output format

  myfile << left << setprecision(8) << setw(15) << state_time;
  for(int i = 0; i < n_vars; i++){
    myfile << left << setprecision(8) << setw(15) << state_array[i];
  }
  myfile << "\n";

  return 0;
}

bool Realization::rates_are_zero(){
  double total_rate = 0;
  for(int i = 0; i < n_events; i++){
    total_rate += rates[i];
  }
  return !(total_rate > 0);
}


DirectMethod::DirectMethod(Model *the_model, const Paramset & the_paramset, rng *the_rng, int n_vars, int n_events) :
  Realization(the_model, the_paramset, the_rng, n_vars, n_events)
{
  waiting_times = new double[n_events];
}

DirectMethod::~DirectMethod(){
  delete waiting_times;
}

int DirectMethod::step(){
  // update waiting times

  int min_ind = 0;
  int i;
  for(i = 0; i < n_events; i++){
    waiting_times[i] = the_rng->rexp(rates[i]);
    if(waiting_times[i] < waiting_times[min_ind]){
      min_ind = i;
    }
  }

  // update time and do event
  state_time += waiting_times[min_ind];
  the_model->updateState(min_ind, state_array);

  return 0;
}
