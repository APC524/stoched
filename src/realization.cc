#include <random>
#include "realization.h"

using namespace Eigen;

Realization::Realization(const Model & the_model, const Paramset & the_paramset) :
  the_model(the_model),
  the_paramset(the_paramset)
{
  set_to_initial_state();
}


Realization::set_to_initial_state(){
  // create state_array and set to initial values 
  state_array = the_paramset.initial_values.replicate(1, 1);
  
  // set state_time to its initial value
  state_time = the_paramset.t_initial;

  // create rates array and set to initial rates
  rates = the_model.rate_function(state_time, state_array,
                                  the_paramset.rate_params);
}


// simulates the realization from t_inital to t_final
Realization::simulate(){
  t_initial = the_paramset.t_initial;
  t_final = the_paramset.t_final;

  int max_stop = 0;
  int rate_stop = 0;
  int iter_count=1;
  int done = 0;

  // add logic here to check that all conditions below are met initially
  rates = the_model.rate_function(state_time, state_array,
                                  the_paramset.rate_params);

  while(done==0){

    /* check that stop conditions haven't been reached
       (maybe wrap this in a function) */ 
    if(state_time > t_final || iter_count > max_ierations){
      max_stop==1;
    }
    
    if(rates.isZero(0)){
        rate_stop = 1;
      }
    
    }
    if(max_stop==1 || rate_stop==1){
      done = 1;
    }

    // take step according to method
    step();

    // output state of the simuation
    output_state();
    
    // update rates and increment iteration count
    rates = the_model.rate_function(state_time, state_array,
                                    the_paramset.rate_params);
    iter_count++;

  
}

// prints the current state of the simulation
Realization::output_state(){
  // to be modified depending on ultimately
  // chosen output format
  printf("%15.8f", state_time);

  for(int = 0; i < the_model.n_vars; i++){
    printf("%15.8f", state_array(i))
  }

}
