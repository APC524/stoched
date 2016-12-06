#include <random>
#include "realization.h"
#include "xoroshiro128plus.h"
#include <math.h>
#include <stdio.h>

using namespace Eigen;

Realization::Realization(const Model & the_model, const Paramset & the_paramset, const rng & the_rng) :
  the_model(the_model),
  the_paramset(the_paramset),
  n_vars(the_model.n_vars)
{
  set_to_initial_state();
}


virtual Realization::~Realization(){
  delete state_array;
  delete rates;
  delete state_time;
}


int Realization::set_to_initial_state(){
  // create state_array and set to initial values 
  state_array = the_paramset.initial_values.replicate(1, 1);
  
  // set state_time to its initial value
  state_time = the_paramset.t_initial;

  // create rates array and set to initial rates
  rates = the_model.rate_function(state_time, state_array,
                                  the_paramset.rate_params);

  return 0;
}


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
  rates = the_model.rate_function(state_time, state_array,
                                  the_paramset.rate_params);

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
    rates = the_model.rate_function(state_time, state_array,
                                    the_paramset.rate_params);
    iter_count++;
  }
}

// prints the current state of the simulation
Realization::output_state(){
  // to be modified depending on ultimately
  // chosen output format
  printf("%15.8f", state_time);

  for(int = 0; i < n_vars; i++){
    printf("%15.8f", state_array(i))
  }

}


DirectMethod::DirectMethod(const Model & the_model, const Paramset & the_paramset) :
  Realization(const Model & the_model, const Paramset & the_paramset)
{
  waiting_times = new VectorXd(the_model.n_events).Zero();
  random_numbers = new VectorXd(the_model.n_events).Zero();
}

DirectMethod::~DirectMethod(){
  delete waiting_times;
  delete random_numbers;
}

DirectMethod::step(){
  for(int i = 0; i < n_vars; i++){
    random_numbers(i) = the_rng.runif();
  }
  waiting_times = (-1/rates) * log(random_numbers);
  std::cout << waiting_times;
}
