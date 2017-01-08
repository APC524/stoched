/** 
 *  @file    model.cc
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
#include "model.h"
#include "fparser/fparser.hh"
#include <assert.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/**
 *   @brief  Default  constructor for Model  
 *  
 *   @param  none   
 *   @return nothing 
 */ 

Model:: Model() {
}

/**
 *   @brief  Destructor of Model  
 *  
 *   @param  none
 *   @return nothing 
 */ 
Model:: ~Model() {
}

/**
 *   @brief  Add variable list to a Model
 *  
 *   @param  vars is a string used to set variables associate with a Model
 *   @return void
 */ 
void Model::addVars(string vars) {
  vars_ = vars;
}

/**
 *   @brief  Add Event to Model's list of Events
 *  
 *   @param  functionRate is a string that defines an Event's rate
 *   @return void
 */ 
void Model::addEvent(string functionRate) {
  eventPtrList.push_back(new Event);
  eventPtrList.back()->setRate(functionRate, vars_);
}

/**
 *   @brief  Add Event function to specified Event in Model
 *  
 *   @param  iEvent is an int that indexes Event list
 *   @param  function is a string that specifies Event function
 *   @return void
 */ 
void Model::addEventFct(int iEvent, string function) {
  eventPtrList[iEvent]->addFunction(function, vars_);

}

/**
 *   @brief  Evaluate given function in specified Event
 *  
 *   @param  iEvent is an int that indexes Event list
 *   @param  iFunction is an int that indexes an Event's Function list
 *   @param  stateArray is a double array specifiying variable values of a function
 *   @return evaluated function as a double
 */ 
double Model::useEventFct(int iEvent, int iFunction, double *stateArray) {
  return eventPtrList[iEvent]->useFunction(iFunction, stateArray);

}

/**
 *   @brief  Evaluate rate function for a specified Event
 *  
 *   @param  iEvent is an int that indexes Event list
 *   @param  stateArray is a double array specifiying variable values of a function
 *   @return evaluated rate function as a double
 */ 
double Model::getEventRate(int iEvent, double *stateArray) {
  return eventPtrList[iEvent]->getRate(stateArray);

}

<<<<<<< HEAD
/**
 *   @brief  Update state array by evaluating all functions of a given Event
 *  
 *   @param  iEvent is an int that indexes Event list
 *   @param  stateArray is a double array specifiying variable values of a function
 *   @return void
 */ 
void Model::updateState(int iEvent, double *stateArray) {
  int var_count = 1;  
  int fct_count = eventPtrList[iEvent]->getSize();
  double stateCopy[fct_count];
}


int Model::getVarsCount() {
  // Returns total number of variables. 
  int var_count = 1;
  for (int i = 0; i < vars_.length(); i++) {
    if (vars_[i] == ',') var_count++;
  }
  return var_count;
}

string Model::getIthVar(int index) {
  // Returns the ith variable in the variable list. 
  istringstream ss(vars_);
  string token;
  for(int i=0; i < index+1; i++){
    getline(ss, token, ',');
  }
  return token;
}


void Model::updateState(int iEvent, double *stateArray) {
  int fct_count = eventPtrList[iEvent]->getSize();
  double stateCopy[fct_count];

  int var_count = getVarsCount();
  assert(var_count == fct_count);

  for (int i = 0; i < fct_count; i++)
    stateCopy[i] = 0.0;

  for (int i = 0; i < fct_count; i++)
    stateCopy[i] = useEventFct(iEvent, i, stateArray);

  for (int i = 0; i < fct_count; i++)
    stateArray[i] = stateCopy[i];

}

/**
 *   @brief  Update rate for all Events in Model's Event list
 *  
 *   @param  stateArray is a double array specifiying variable values of a function
 *   @param  rateArray is a double array specifiying variable values of a rate function
 *   @return void
 */ 
void Model::updateRates(double *stateArray, double *rateArray) {
  int event_count = eventPtrList.size();
  double rateCopy[event_count];

  for (int i = 0; i < event_count; i++)
    rateCopy[i] = 0.0;

  for (int i = 0; i < event_count; i++)
    rateCopy[i] = getEventRate(i, stateArray);

  for (int i = 0; i < event_count; i++)
    rateArray[i] = rateCopy[i];

}
