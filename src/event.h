#ifndef EVENT_H_
#define EVENT_H_
#include "fparser.h"

/* class to hold user-specified events, namely sets of functions */

class Event {
 public: 
  Event( );
  ~Event();
  functionParser *addFunction();
  double setRate();

 private:
  functionParser *functionArray;
  double rate;
};

#endif  


