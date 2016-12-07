// testevent.cc
#include <iostream>
#include <string>
#include <stdio.h>
#include "event.h"
#include "model.h"
#include "paramset.h"
#include "realization.h"
#include "xoroshiro128plus.h"

using namespace std;

int main() {
  
  string variables = "a,b,c";
  double args[3] = {1.0, 2.0, 4.0};
  double rateArray[2] = {0.0, 0.0};

  string function1A = "a + 1";
  string function1B = "b + 0";
  string function1C = "c + 0";
  string rateFunction1 = "(a+b)/(a+b+c)";

  string function2A = "a - 1";
  string function2B = "b + 1";
  string function2C = "c + 1";
  string rateFunction2 = "(c+a)/(a+b+c)";

  Model *model_ptr;
  Model model;

  model_ptr = & model;
  
  model.addVars(variables);

  model.addEvent(rateFunction1);
  model.addEventFct(0, function1A);
  model.addEventFct(0, function1B);
  model.addEventFct(0, function1C);

  model.addEvent(rateFunction2);
  model.addEventFct(1, function2A);
  model.addEventFct(1, function2B);
  model.addEventFct(1, function2C);

  int method = 0;
  int n_vars = 3;
  int n_events = 2;
  double inits[3] = {1.0, 2.0, 3.0};
  double t_initial = 0;
  double t_final = 100;
  double timestep_size = 0.5;
  double n_realizations = 1;
  double max_iter = 10000000;
  int seed = 502;
  Paramset paramset(method, n_vars, inits, t_initial,
                    t_final, timestep_size, n_realizations,
                    max_iter, seed);

  xoroshiro128plus* rng_ptr = new xoroshiro128plus(seed);

  DirectMethod realization(model_ptr, paramset, rng_ptr, n_vars, n_events);
  realization.simulate();

  cout << "Model starting state: a = " << args[0] << ", b = " << args[1] << ", c = " << args[2] << endl;
  
  cout << "Function 1A: a*b*c = " << model.useEventFct(0, 0, args) << endl;
  cout << "Function 1B: a+b+c = " << model.useEventFct(0, 1, args) << endl;
  cout << "Function 1C: c*b-a = " << model.useEventFct(0, 2, args) << endl;

  cout << "Function 2A: a+b*c = " << model.useEventFct(1, 0, args) << endl;
  cout << "Function 2B: a*b-c = " << model.useEventFct(1, 1, args) << endl;
  cout << "Function 2C: (a-b)*c = " << model.useEventFct(1, 2, args) << endl;

  cout << "Rate Function 1: 5*(a+b) = " << model.getEventRate(0, args) << endl;
  cout << "Rate Function 2: c*(a+b) = " << model.getEventRate(1, args) << endl;

  model.updateRates(args, rateArray);
  cout << "Event Rates - input 1: event1 = " << rateArray[0] << ", event2 = " << rateArray[1] << endl;

  model.updateState(0, args);
  cout << "Update state - event1: a = " << args[0] << ", b = " << args[1] << ", c = " << args[2] << endl;

  model.updateState(1, args);
  cout << "Update state - event2: a = " << args[0] << ", b = " << args[1] << ", c = " << args[2] << endl;

  delete rng_ptr;
  return 0;
}
