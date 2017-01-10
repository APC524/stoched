// testevent.cc
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "event.h"
#include "model.h"
#include "paramset.h"
#include "realization.h"
#include "xoroshiro128plus.h"
#include "nextreaction.h"
#include "firstreaction.h"


//using namespace std;
using namespace std::chrono;

int main() {
  
  string variables = "a,b";
  double args[2] = {1.0, 2.0};
  double rateArray[2] = {0.0, 0.0};

  string function1A = "a + 1";
  string function1B = "b + 0";
  string rateFunction1 = "3";

  string function2A = "a - 1";
  string function2B = "b + 0";
  string rateFunction2 = "a / 3";

  string function3A = "a + 0";
  string function3B = "b + 1";
  string rateFunction3 = "5 * a";
 
  string function4A = "a + 0";
  string function4B = "b - 1";
  string rateFunction4 = "b / 30";
  
  Model *model_ptr;
  Model model;

  model_ptr = & model;
  
  model.addVars(variables);

  model.addEvent(rateFunction1);
  model.addEventFct(0, function1A);
  model.addEventFct(0, function1B);

  model.addEvent(rateFunction2);
  model.addEventFct(1, function2A);
  model.addEventFct(1, function2B);

  model.addEvent(rateFunction3);
  model.addEventFct(2, function3A);
  model.addEventFct(2, function3B);
  
  model.addEvent(rateFunction4);
  model.addEventFct(3, function4A);
  model.addEventFct(3, function4B);

  int method = 0;
  int n_vars = 2;
  int n_events = 4;
  double inits[2] = {0.0, 0.0};
  double t_initial = 0;
  double t_final = 5000;
  double timestep_size = 0.5;
  double n_realizations = 1;
  double max_iter = 100000000;
  int seed = 502;
  Paramset paramset(method, n_vars, inits, t_initial,
                    t_final, timestep_size, n_realizations,
                    max_iter, seed);

  xoroshiro128plus* rng_ptr = new xoroshiro128plus(seed);

  // Open file
  ofstream myfile;
  myfile.open ("example_output.txt");

  // Write the header line corresponding to model
  myfile << left << setw(15) << "time";
  int vars_count = model.getVarsCount(); 
  for(int i = 0; i < n_vars; i++){
    string test = model.getIthVar(i);
    myfile << left << setw(15) <<  test;
  }
  myfile << "\n";
  
  // Run realization simulation
  //DirectMethod realization(model_ptr, paramset, rng_ptr, n_vars, n_events);
  //realization.simulate(myfile);




  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  NextReaction realization(model_ptr, paramset, rng_ptr, n_vars, n_events);
  realization.simulate(myfile);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  myfile << "\n";
  myfile << left << setw(15) << "time";
  vars_count = model.getVarsCount(); 
  for(int i = 0; i < n_vars; i++){
    string test = model.getIthVar(i);
    myfile << left << setw(15) <<  test;
  }
  myfile << "\n";

  auto duration_first = duration_cast<microseconds>( t2 - t1 ).count();

  high_resolution_clock::time_point t3 = high_resolution_clock::now();
  FirstReaction realization2(model_ptr, paramset, rng_ptr, n_vars, n_events);
  realization2.simulate(myfile);
  high_resolution_clock::time_point t4 = high_resolution_clock::now();
  // Close the file 
  myfile.close();

  auto duration_next = duration_cast<microseconds>( t4 - t3 ).count();

  printf("First rxn ran in %15.8f seconds \n", duration_first * 1.0e-6);
  printf("Next rxn ran in %15.8f seconds \n", duration_next * 1.0e-6);
  
  delete rng_ptr;

  return 0;
}






