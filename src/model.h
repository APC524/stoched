#ifndef MODEL_H_
#define MODEL_H_
#include "event.h"
#include <vector>


using namespace std;

/**  
 *  @brief Class MODEL, which holds user-specified models 
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

  // Add variable list to Model
  void addVars(string vars);
  
  // Add an Event to Model's list of Events
  void addEvent(string functionRate);

  // Add an Event function to specified Event in Model
  void addEventFct(int iEvent, string function);

  // Evaluate given function in specified Event
  double useEventFct(int iEvent, int iFunction, double *stateArray);

  // Evaluate rate function for specified Event
  double getEventRate(int iEvent, double *stateArray);

  // Update state array by evaluation all functions of a given Event
  void updateState(int iEvent, double *stateArray);

  // Update rate for all Events in Model's Event list
  void updateRates(double *stateArray, double *rateArray);
 
private:
  vector<Event*> eventPtrList; ///< List of Events in Model
  string vars_;                ///< Variables associated with a model

};

#endif
