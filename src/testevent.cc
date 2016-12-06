// testevent.cc
#include <iostream>
#include <string>
#include <stdio.h>
#include "event.h"

using namespace std;

int main() {
  
  string function1 = "a*b*c";
  string function2 = "a+b+c";
  string variables = "a,b,c";
  string rateFunction = "5*(a+b)";
  double args[3] = {1.0, 2.0, 4.0};

  Event event;
  event.setRate(rateFunction, variables);
  event.addFunction(function1, variables);
  event.addFunction(function2, variables);
  cout << "Variables: a = " << args[0] << ", b = " << args[1] << ", c = " << args[2] << endl;
  cout << "Function 1: a*b*c = " << event.useFunction(0, args) << endl;
  cout << "Function 2: a+b+c = " << event.useFunction(1, args) << endl;
  cout << "Rate Function: 5*(a+b) = " << event.getRate(args) << endl;

  return 0;
}
