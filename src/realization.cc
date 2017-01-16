/** 
 *  @file    realization.cc
 *  @author  Dylan Morris (dhmorris@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Class Realization holds realizations of a Model 
 *         (state array, propensities, waiting times, etc.) 
 *  
 */

#include "realization.h"

using namespace std;

/**
 *   @brief  Default constructor for Realization  
 *  
 *   @param  the_model is a Model object
 *   @param  the_paramset is a Paramset object
 *   @param  the_rng is a random number generator 
 *   @param  n_vars is an int specifying variable count
 *   @param  n_events is an int specifying event count
 * 
 *   @return nothing 
 */ 
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

/**
 *   @brief  Destructor of Realization
 *  
 *   @return nothing 
 */ 
Realization::~Realization(){
  delete state_array;
  delete rates;
}

/**
 *   @brief Sets state_array and state_time to their user-specified initial values
 *  
 *   @return int
 */ 
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

/**
 *   @brief Simulates the realization from t_inital to t_final
 *  
 *   @return int
 */ 
int Realization::simulate(std::ofstream& myfile, std::string write_out_path){
  double t_final = the_paramset.t_final;
  int max_iter = the_paramset.max_iter;
  int suppress_output = the_paramset.suppress_output;
  
  int iter_count = 1;
  bool done = 0;

  set_to_initial_state();

  while(done==0){

    // take step according to method
    step();

    // output state of the simuation
    if(suppress_output==0)
      output_state(myfile);
    
    // increment iteration count
    iter_count++;

    /* check that stop conditions haven't been reached
       (maybe wrap this in a function) */ 
    if(state_time > t_final){
      done = 1;
    }
    else if (iter_count > max_iter) {
      done = 1;
    }
    else if(rates_are_zero()){
      done = 1;
    }
  }

  if(suppress_output==1){
    myfile.open(write_out_path);
    output_state(myfile);
    myfile.close();
  }

  return 0;
}

/**
 *   @brief  Prints the current state of the simulation
 *  
 *   @return int 
 */ 

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

/**
 *   @brief checks whether all rates are zero
 *
 *   @return bool
 */
bool Realization::rates_are_zero(){
  bool val = 1;
  for(int i = 0; i < n_events; i++){
    if (abs(rates[i]) < 1e-14){
      rates[i] = 0.0;
    }
    if(rates[i] < 0.0) {
      throw runtime_error("Negative rate. Rates must always "
                          "be greater than or equal to zero");
    };

    if(rates[i] > DBL_MIN){
      val = 0;
    };
  }
  return val;
}
