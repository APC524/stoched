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

using namespace std;

/* class to hold user-specified models of stochastic systems
 so that realizations from them can be simulated */

Model:: Model() {
}

Model:: ~Model() {
}

void Model::addVars(string vars) {
  vars_ = vars;
}

void Model::addEvent(string functionRate) {
  eventPtrList.push_back(new Event);
  eventPtrList.back()->setRate(functionRate, vars_);
}

void Model::addEventFct(int iEvent, string function) {
  eventPtrList[iEvent]->addFunction(function, vars_);

}

double Model::useEventFct(int iEvent, int iFunction, double *stateArray) {
  return eventPtrList[iEvent]->useFunction(iFunction, stateArray);

}

double Model::getEventRate(int iEvent, double *stateArray) {
  return eventPtrList[iEvent]->getRate(stateArray);

}

void Model::updateState(int iEvent, double *stateArray) {
  int var_count = 1;  
  int fct_count = eventPtrList[iEvent]->getSize();
  double stateCopy[fct_count];

  for (int i = 0; i < vars_.length(); i++) {
    if (vars_[i] == ',') var_count++;
  }

  assert(var_count == fct_count);

  for (int i = 0; i < fct_count; i++)
    stateCopy[i] = 0.0;

  for (int i = 0; i < fct_count; i++)
    stateCopy[i] = useEventFct(iEvent, i, stateArray);

  for (int i = 0; i < fct_count; i++)
    stateArray[i] = stateCopy[i];

}

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
 


