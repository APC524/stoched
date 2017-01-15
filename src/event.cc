/** 
 *  @file    event.cc
 *  @author  Caleb Peckham (peckham@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Class Event holds a user-specified event, namely set of 
 *         functions and associated rate
 *  
 */

#include "event.h"
#include "fparser/fparser.hh"
#include <assert.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
//#include "gtest/gtest.h"

using namespace std;

/**
 *   @brief  Default constructor for Event  
 *  
 *   @param  eq_count is the size of the function array
 *   @param  functionArray contains all user-specified FunctionParsers that govern event   
 *   @return nothing 
 */ 
Event::Event() {
  eq_count_ = 0;
  functionArray_ = (FunctionParser **)malloc(sizeof(FunctionParser));
  deltaVar_ = (double*)malloc(sizeof(double));
}
  
/**
 *   @brief  Destructor of Event  
 *  
 *   @return nothing 
 */ 
Event::~Event() {
  free(deltaVar_);
  free(functionArray_); 
}

/**
 *   @brief  Add a function parser to the function array
 *  
 *   @param  function is a string used to generate a FunctionParser object
 *   @param  variables is a string used to generate a FunctionParser object
 *   @return void
 */ 
void Event::addFunction(string function, string variables) {
  // count how many variables there are
  int varsCount_ = 1;
  for (int i = 0; i < variables.length(); i++) {
    if (variables[i] == ',') varsCount_++;
  }

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
  // allocate memory so that a continuous derivative delta can be added
  if (eq_count_ != 0){
    deltaVar_ = (double*)realloc(deltaVar_,varsCount_*sizeof(double));
  }
  eq_count_++;
}

/**
 *   @brief  Evaluate function stored at specified spot in the function array
 *  
 *   @param  iFunction is an int that indexes function array
 *   @param  stateArray is a double array specifying variable values of function
 *   @return evaluated functionParser as a double
 */ 
double Event::useFunction(int iFunction, double *stateArray) {
  return  functionArray_[iFunction]->Eval(stateArray);
}

/**
 *   @brief Set equation for rateFunction
 *  
 *   @param  function is a string used for parsing rateFunction
 *   @param  variables is a string used for parsing rateFunction
 *   @return void
 */ 
void Event::setRate(string function, string variables) {
  int res = rateFunction.Parse(function, variables);

  if (res >= 0) {
    fprintf(stderr, "Error!\n");
    exit(-1);
  }

}

/**
 *   @brief Return rate to user based on values of the state array
 *  
 *   @param  stateArray is a double array specifying variable values of function
 *   @return evaluated rateFunction as a double
 */ 
double Event::getRate(double *stateArray) {
  return rateFunction.Eval(stateArray);
}

/**
 *   @brief Return size of event, namely number of functions, to user  
 *
 *   @return size of event, namely number of functions, as an int
 */ 
int Event::getSize() {
  return eq_count_;
}

/**
 *   @brief Return how the ith variable is incremented when the ith equation is called
 *
 *   @param  i is an int specifying of which variable to find the delta.
0 is the first variable
 *   @return change in value of i when its corresponding equation is called, as a double
 */ 
double Event::getDeltaVar(int i) {
  if (i >= eq_count_){
    fprintf(stderr, "Error: Array bounds exceeded. Asked for a derivate\n"
            "in the contDeriv array that does not exist\n");
    exit(1);
  }
  return deltaVar_[i];
}

/**
 *   @brief set the amount that the ith function increments the ith variable. This is used by midpoint tau leaping
 *
 *   @param  i is an int specifying of which variable to set. 0 is the first variable
 *   @return void
 */ 
void Event::setDeltaVar(int i, double val) {
  if (i >= eq_count_){
    fprintf(stderr, "Error: Array bounds exceeded. Tried to set a derivate\n"
            "in the contDeriv array that does not exist\n");
    exit(1);
  }
  deltaVar_[i] = val;
}
