// testevent.cc
#include <iostream>
#include <string>
#include <stdio.h>
#include "event.h"
#include "model.h"

using namespace std;

int main() {
  
  string variables = "a,b,c";

  string function1A = "a*b*c";
  string function1B = "a+b+c";
  string function1C = "c*b-a";
  string rateFunction1 = "5*(a+b)";

  string function2A = "a+b*c";
  string function2B = "a*b-c";
  string function2C = "(a-b)*c";
  string rateFunction2 = "c*(a+b)";

  double args1[3] = {1.0, 2.0, 4.0};
  double args2[3] = {5.0, 4.0, 6.0};

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

  cout << "Event 1 Variables: a = " << args1[0] << ", b = " << args1[1] << ", c = " << args1[2] << endl;
  cout << "Event 2 Variables: a = " << args2[0] << ", b = " << args2[1] << ", c = " << args2[2] << endl;
  
  cout << "Function 1A: a*b*c = " << model.useEventFct(0, 0, args1) << endl;
  cout << "Function 1B: a+b+c = " << model.useEventFct(0, 1, args1) << endl;
  cout << "Function 1C: c*b-a = " << model.useEventFct(0, 2, args1) << endl;

  cout << "Function 2A: a+b*c = " << model.useEventFct(1, 0, args2) << endl;
  cout << "Function 2B: a*b-c = " << model.useEventFct(1, 1, args2) << endl;
  cout << "Function 2C: (a-b)*c = " << model.useEventFct(1, 2, args2) << endl;

  cout << "Rate Function A: 5*(a+b) = " << model.getEventRate(0, args1) << endl;
  cout << "Rate Function B: c*(a+b) = " << model.getEventRate(1, args2) << endl;

  model.updateState(0, args1);
  cout << "Event1 Variables: a = " << args1[0] << ", b = " << args1[1] << ", c = " << args1[2] << endl;

  model.updateState(1, args2);
  cout << "Event2 Variables: a = " << args2[0] << ", b = " << args2[1] << ", c = " << args2[2] << endl;

  return 0;
}
