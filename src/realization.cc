#include "realization.h"

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
int Realization::simulate(std::ofstream& myfile){
  double t_initial = the_paramset.t_initial;
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
    output_state(myfile);
    
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

// checks whether all rates are zero
bool Realization::rates_are_zero(){
  for(int i = 0; i < n_events; i++){
    if(rates[i] > DBL_MIN){
      return 0;
    };
  }
  return 1;
}

