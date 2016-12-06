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
  cout << event.useFunction(0, args) << endl;
  cout << event.useFunction(1, args) << endl;
  cout << event.getRate(args) << endl;

  return 0;
}
