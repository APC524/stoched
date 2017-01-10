/** 
 *  @file    model.h
 *  @author  Caleb Peckham (peckham@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief APC 524, Final Project - Stoched 
 *
 *  @section DESCRIPTION
 *  
 */

#ifndef MODEL_H_
#define MODEL_H_
#include "event.h"
#include <vector>
#include <sstream>
#include <string>

using namespace std;

/**  
 *  @brief Class Model, which holds user-specified models 
 *  of stochastic systems from which realizations are to
 *  be simulated. A model may have variable parameters; 
 *  each complete set will be stored in an object of class Paramset
 */  

class Model {

 public:

  // Default constructor for Model
  Model();        

  // Destructor of Model 
  ~Model();

  // Add variable list to a Model
  void addVars(string vars);
  
  // Add Event to Model's list of Events
  void addEvent(string functionRate);

  // Add Event function to specified Event in Model
  void addEventFct(int iEvent, string function);

  // Evaluate given function in specified Event
  double useEventFct(int iEvent, int iFunction, double *stateArray);

  // Evaluate rate function for a specified Event
  double getEventRate(int iEvent, double *stateArray);

  // Returns total number of variables. 
  int getVarsCount();

  // Returns total number of events
  int getEventsCount();

  // Returns the ith variable in the variable list
  string getIthVar(int index);

  // Update state array by evaluation all functions of a given Event
  void updateState(int iEvent, double *stateArray);

  // Update rate for all Events in Model's Event list
  void updateRates(double *stateArray, double *rateArray);
 
private:
  vector<Event*> eventPtrList; ///< List of Events in Model
  string vars_;                ///< Variables associated with a model

};

#endif
