// testevent.cc
#include <iostream>
#include <string>
#include <stdio.h>
#include "event.h"
#include "model.h"

using namespace std;

int main() {
  
  string functionA1 = "a*b*c";
  string functionA2 = "a+b+c";
  string variables = "a,b,c";
  string rateFunctionA = "5*(a+b)";

  string functionB1 = "a+b*c";
  string functionB2 = "a*b-c";
  string rateFunctionB = "c*(a-b)";

  double argsA[3] = {1.0, 2.0, 4.0};
  double argsB[3] = {5.0, 4.0, 6.0};

  Model model;

  model.addVars(variables);

  model.addEvent(rateFunctionA);
  model.addEvent(rateFunctionB);

  model.addEventFct(0, functionA1);
  model.addEventFct(0, functionA2);

  model.addEventFct(1, functionB1);
  model.addEventFct(1, functionB2);

  cout << "A Variables: a = " << argsA[0] << ", b = " << argsA[1] << ", c = " << argsA[2] << endl;
  cout << "B Variables: a = " << argsB[0] << ", b = " << argsB[1] << ", c = " << argsB[2] << endl;
  
  cout << "Function A1: a*b*c = " << model.useEventFct(0, 0, argsA) << endl;
  cout << "Function A2: a+b+c = " << model.useEventFct(0, 1, argsA) << endl;

  cout << "Function B1: a+b*c = " << model.useEventFct(1, 0, argsB) << endl;
  cout << "Function B2: a*b-c = " << model.useEventFct(1, 1, argsB) << endl;

  cout << "Rate Function A: 5*(a+b) = " << model.getEventRate(0, argsA) << endl;
  cout << "Rate Function B: c*(a-b) = " << model.getEventRate(1, argsB) << endl;

  return 0;
}
