#ifndef EVENT_H_
#define EVENT_H_
#include "fparser/fparser.hh"

using namespace std;

// Class to hold user-specified events, namely sets of functions 
class Event {
 public: 
  Event();
  ~Event();
  void addFunction(string function, string variables);
  double useFunction(int iFunction, double *args);
  void setRate(string function, string variables);
  double getRate(double *args);
  int getSize();
  string eventName;

 private:
  FunctionParser **functionArray_;
  FunctionParser rateFunction;
  double rate_;
  int eq_count_;

};

#endif  


