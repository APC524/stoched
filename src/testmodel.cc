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

  Model model(variables);
  model.addEvent(rateFunctionA);
  model.addEvent(rateFunctionB);

  model.addEventFct(0, functionA1);
  model.addEventFct(0, functionA2);

  model.addEventFct(1, functionB1);
  model.addEventFct(1, functionB2);

  cout << model.useEventFct(0, 0, argsA) << endl;
  cout << model.useEventFct(0, 1, argsA) << endl;

  cout << model.useEventFct(1, 0, argsB) << endl;
  cout << model.useEventFct(1, 1, argsB) << endl;

  cout << model.getEventRate(0, argsA) << endl;
  cout << model.getEventRate(1, argsB) << endl;

  return 0;
}
