// testevent.cc
#include <iostream>
#include <string>
#include <stdio.h>
#include "event.h"
#include "model.h"

using namespace std;

int main() {
  
  string variables = "a,b,c";
  double args[3] = {1.0, 2.0, 4.0};
  double rateArray[2] = {0.0, 0.0};

  string function1A = "a*b*c";
  string function1B = "a+b+c";
  string function1C = "c*b-a";
  string rateFunction1 = "5*(a+b)";

  string function2A = "a+b*c";
  string function2B = "a*b-c";
  string function2C = "(a-b)*c";
  string rateFunction2 = "c*(a+b)";

  Model model;

  model.addVars(variables);

  model.addEvent(rateFunction1);
  model.addEventFct(0, function1A);
  model.addEventFct(0, function1B);
  model.addEventFct(0, function1C);

  model.addEvent(rateFunction2);
  model.addEventFct(1, function2A);
  model.addEventFct(1, function2B);
  model.addEventFct(1, function2C);

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

  return 0;
}
