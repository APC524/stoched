#ifndef EVENT_H_
#define EVENT_H_
#include "fparser.hh"

/* class to hold user-specified events, namely sets of functions */

class Event {
 public: 
  Event( );
  ~Event();
  functionParser *addFunction();
  double setRate();

 private:
  FunctionParser *functionArray;
  double rate;
};

#endif  


