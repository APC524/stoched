#ifndef MODEL_H_
#define MODEL_H_
#include "event.h"
#include <vector>

using namespace std;

/* class to hold user-specified models of stochastic systems
 so that realizations from them can be simulated */

class Model {
 public:
  Model(string vars);
  ~Model();
  void addEvent(string functionRate);
  void addEventFct(int iEvent, string function);
  double useEventFct(int iEvent, int iFunction, double *stateArray);
  double getEventRate(int iEvent, double *stateArray);
  void updateState(int iEvent, double *stateArray);
 
private:
  vector<Event*> eventPtrList;
  string vars_;

};

#endif
