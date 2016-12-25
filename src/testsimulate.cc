// testevent.cc
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sys/time.h>
#include <iomanip>
#include "event.h"
#include "model.h"
#include "paramset.h"
#include "realization.h"
#include "xoroshiro128plus.h"


using namespace std;

int main() {
  
  // Initialize timer (to get total runtime)
  struct timeval t1, t2;
  gettimeofday(&t1, NULL);

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
  double t_final = 4000;
  double timestep_size = 0.5;
  double n_realizations = 1;
  double max_iter = 10000000;
  int seed = 502;
  Paramset paramset(method, n_vars, inits, t_initial,
                    t_final, timestep_size, n_realizations,
                    max_iter, seed);

  xoroshiro128plus* rng_ptr = new xoroshiro128plus(seed);

  // Open file
  ofstream myfile;
  myfile.open ("example.txt");

  // Write the header line corresponding to model
  myfile << left << setw(15) << "time";
  int vars_count = model.getVarsCount(); 
  for(int i = 0; i < n_vars; i++){
    string test = model.getIthVar(i);
    myfile << left << setw(15) <<  test;
  }
  myfile << "\n";
  
  // Run realization simulation
  DirectMethod realization(model_ptr, paramset, rng_ptr, n_vars, n_events);
  realization.simulate(myfile);

  // Close the file 
  myfile.close();

  delete rng_ptr;

  // Output runtime:
  gettimeofday(&t2, NULL);
  int milliSeconds = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec)/1000;
  double timediff = (double)(milliSeconds)/1000.0;
  printf ("Runtime: %f seconds.\n",timediff);

  return 0;
}






