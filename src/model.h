/* ------------- class Model -------------

   Header for class MODEL, which holds user-specified models 
   of stochastic systems from which realizations are to
   be simulated. A model may have variable parameters; 
   each complete set will be stored in an object of class
   Paramset

*/


#ifndef MODEL_H_
#define MODEL_H_
#include "event.h"
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Model {

 public:
  Model();
  ~Model();
  void addVars(string vars);
  void addEvent(string functionRate);
  void addEventFct(int iEvent, string function);
  double useEventFct(int iEvent, int iFunction, double *stateArray);
  double getEventRate(int iEvent, double *stateArray);
  int getVarsCount();
  int getEventsCount();
  string getIthVar(int index);
  void updateState(int iEvent, double *stateArray);
  void updateRates(double *stateArray, double *rateArray);
 
private:
  vector<Event*> eventPtrList;
  string vars_;

};

#endif
