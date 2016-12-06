#include "event.h"
#include "model.h"
#include "fparser/fparser.hh"
#include <assert.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

// model.cc

/* class to hold user-specified models of stochastic systems
 so that realizations from them can be simulated */

Model:: Model(string vars) {
  vars_ = vars;
}

Model:: ~Model() {

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

//void Model::updateState(int iEvent, double *stateArray) {

//}
 


