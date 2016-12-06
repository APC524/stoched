/* ------------- class Model -------------

   Header for class MODEL, which holds user-specified models 
   of stochastic systems from which realizations are to
   be simulated. A model may have variable parameters; 
   each complete set will be stored in an object of class
   Paramset

*/


#ifndef MODEL_H_
#define MODEL_H_
#include <Eigen/Core>
#include <Eigen/LU>
#include "event.h"



class Model {
  using namespace Eigen;

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
