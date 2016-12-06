#include "event.h"
#include "fparser/fparser.hh"
#include <assert.h>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

// event.cc

// Constructor of Event class
Event::Event() {
  eq_count_ = 0;
  functionArray_ = (FunctionParser **)malloc(sizeof(FunctionParser));
}
  
// Destructor of Event 
Event::~Event() {
  
  free (functionArray_); 
}

// Add a function parser, consisting of a function and associated variables
void Event::addFunction(string function, string variables) {

  if (eq_count_ != 0) {
    functionArray_  = (FunctionParser**)realloc(functionArray_, (eq_count_)*sizeof(FunctionParser));
  }
  functionArray_[eq_count_] = new FunctionParser;
  functionArray_[eq_count_]->AddConstant("pi", 3.1415926535897932);
    
  int res =  functionArray_[eq_count_]->Parse(function, variables);
  if (res >= 0) {
    fprintf(stderr, "Error!\n");
    exit(-1);
  }

  eq_count_++;

}

// Use a function parser, consisting of a function and associated variables
double Event::useFunction(int iFunction, double *args) {
  return  functionArray_[iFunction]->Eval(args);

}

// Return value of rate_ to user
void Event::setRate(double rate) {
  rate_ = rate;
}

// Return value of rate_ to user
double Event::getRate() {
  return rate_;
}

