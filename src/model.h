#ifndef MODEL_H_
#define MODEL_H_
#include <Eigen/Core>
#include <Eigen/LU>
#include "event.h"

using namespace Eigen;


/* class to hold user-specified models of stochastic systems
 so that realizations from them can be simulated */

class Model {
 public:
  Model(string vars);
  ~Model();
  void addEvent(double rate);
  void addEventFct(int iEvent, string function);
  double useEventFct(int iEvent, int iFunction, double *stateArray);
  double getEventRate(int iEvent);
  void updateState(int iEvent, double *stateArray);
 
private:
  vector<Event*> eventPtrList;
  const string vars;

}

#endif
