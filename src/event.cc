#include "event.h"
#include "fparser.hh"
#include <assert.h>
#include <iostream>
#include <string.h>

using namespace std;

// event.cc
// class to hold user-specified events, namely sets of functions 

class Event {

  Event::Event(String rate) {
    Function fparser;
 
  }
  
  Event::~Event() {
    delete [] functionArray_; 
  }

  FunctionParser Event::addFunction(String function, String variables) {
    Function fparser;

   int res = fparser.Parse(function, variables);
    if (res >= 0) {
      fprintf(stderr, "Error!\n");
      exit(-1);
    }


  }

  double Event::setRate(String rate) {


  }

}
