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

  Event event;
  event.setRate(42.3);
  event.addFunction(function1, variables);
  event.addFunction(function2, variables);
  cout << event.getRate() << endl;

  return 0;
}
