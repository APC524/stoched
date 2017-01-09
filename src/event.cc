/** 
 *  @file    event.cc
 *  @author  Caleb Peckham (peckham@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief APC 524, Final Project - Stoched 
 *
 *  @section DESCRIPTION
 *  
 */

#include "event.h"
#include "fparser/fparser.hh"
#include <assert.h>
#include <string>
#include <stdio.h>
#include <iostream>

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
}
  
/**
 *   @brief  Destructor of Event  
 *  
 *   @param  none
 *   @return nothing 
 */ 
Event::~Event() {
  
  free (functionArray_); 
}

/**
 *   @brief  Add a function parser to the function array
 *  
 *   @param  function is a string used to generate a FunctionParser object
 *   @param  variables is a string used to generate a FunctionParser object
 *   @return void
 */ 
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
 *   @brief Return size of event, namely number of functions, to user  
 *
 *   @param  None
 *   @return size of event, namely number of functions, as an int
 */ 
int Event::getSize() {
  return eq_count_;
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
