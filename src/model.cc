/** 
 *  @file    model.cc
 *  @author  Caleb Peckham (peckham@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Class Model, which holds user-specified models 
 *  of stochastic systems from which realizations are to
 *  be simulated.
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
 *   Default constructor for Model  
 *  
 *   @return nothing 
 */ 

Model:: Model() {
  tauLeapAvail_ = true;
}

/**
 *   Destructor of Model  
 *  
 *   @return nothing 
 */ 
Model:: ~Model() {
}

/**
 *   Add variable list to a Model
 *  
 *   @param  vars is a string used to set variables associate with a Model
 *   @return void
 */ 
void Model::addVars(string vars) {
  vars_ = vars;
}

/**
 *   Add Event to Model's list of Events
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
 *   @brief  Indicate tau leaping is inpermissible by setting the tauLeapAvail_ flag to false
 *  
 *   @return void
 */
void Model::setTauLeapFalse() {
  tauLeapAvail_ = false;
}

/**
 *   @brief  Check if events are compatible with tau leaping
 *
 *   @return the status of if tau leaping is available as a boolean
 */
bool Model::checkTauLeapAvail() {
  return tauLeapAvail_;
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
 *   @brief  Get a list of the variables that make up the state array
 *   @return comma separated list of variable names as a string
 */
string Model::getVarsString(){
  return vars_;
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

/**
 *   @brief  Return total number of variables
 *  
 *   @return int
 */ 
int Model::getVarsCount() {

  int var_count = 1;
  for (unsigned i = 0; i < vars_.length(); i++) {
    if (vars_[i] == ',') var_count++;
  }
  return var_count;
}


/**
 *   @brief  Return total number of Events
 *
 *   @return int
 */
int Model::getEventsCount() {
  return eventPtrList.size();
}


/**
 *   @brief  Returns the ith variable in the variable list
 *
 *   @param  index is an int that indexes variable list
 *   @return ith variable as string
 */
string Model::getIthVar(int index) {

  istringstream ss(vars_);
  string token;
  for(int i=0; i < index+1; i++){
    getline(ss, token, ',');
  }
  return token;
}

/**
 *   @brief  Returns the continuous time derivative of specified variable
 *
 *   @param  int specifying which variable from the state array to find derivative
 *   @param  double array of the entire state array
 *   @return ith continuous derivative as a double
 */
double Model::getContDeriv(int whichVar, double *stateArray) {
  if (whichVar >= getVarsCount()){
    fprintf(stderr, "Error: Array bounds exceeded. Asked for a derivate\n"
	    "in the contDeriv array that does not exist\n");
    exit(1);
  }
  if (!tauLeapAvail_){
    fprintf(stderr, "Error: tau leaping is not available, so can not access\n"
	    "the continuous time derivative\n");
    exit(1);
  }
  double deriv = 0;
  for (int iEvent = 0; iEvent < getEventsCount(); iEvent++){
    deriv += (eventPtrList[iEvent]->getRate(stateArray))
      * (eventPtrList[iEvent]->getDeltaVar(whichVar));
  }
  return deriv;
}

/**
 *   @brief  Sets the delta of a specified variable in the specified event. This delta is needed to compute the continuous time derivative
 *
 *   @param  int specifying to which variable from the state array the delta corresponds
 *   @param  int specifying to which event the delta corresponds
 *   @param  double specifying the value of delta
 *   @return void
 */
void Model::setDelta(int whichVar, int whichEvent, double val){
  eventPtrList[whichEvent]->setDeltaVar(whichVar, val);
}

/**
 *   @brief  Update state array by evaluating all functions of a given Event
 *  
 *   @param  iEvent is an int that indexes Event list
 *   @param  stateArray is a double array specifiying variable values of a function
 *   @return void
 */
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
  int event_count = getEventsCount();
  double rateCopy[event_count];

  for (int i = 0; i < event_count; i++)
    rateCopy[i] = 0.0;

  for (int i = 0; i < event_count; i++)
    rateCopy[i] = getEventRate(i, stateArray);

  for (int i = 0; i < event_count; i++)
    rateArray[i] = rateCopy[i];
}

