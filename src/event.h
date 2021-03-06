/** 
 *  @file    event.h
 *  @author  Caleb Peckham (peckham@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Class Event holds a user-specified event, namely set of 
 *         functions and associated rate
 *  
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "fparser/fparser.hh"

using namespace std;

/**  
 *  @brief Class Event holds a user-specified event, namely set of 
 *         functions and associated rate
 */  
class Event {
 public: 

  // Default constructor for Event 
  Event();

  // Destructor of Event
  ~Event();

  // Add a function parser to the function array  
  void addFunction(string function, string variables);

  // Evaluate function stored at specified spot in the function array
  double useFunction(int iFunction, double *args);

  // Set equation for rateFunction
  void setRate(string function, string variables);
  
  // Return rate to user based on value of the state array
  double getRate(double *args);

  // Return size of Event, namely number of functions, to user 
  int getSize();
  
  // Return how much the ith eqaution increments the ith equation when it is called
  double getDeltaVar(int i);

  // Set how much the ith eqaution increments the ith equation when it is called
  void setDeltaVar(int i, double val);

  // Specify name of Event object
  string eventName; 

 private:
  FunctionParser **functionArray_; ///< Array of function parsers 
  FunctionParser rateFunction;     ///< Rate specified by an equation
  int eq_count_;                   ///< Number of function parsers
  double* deltaVar_; ///< how much each variable in the state changes when its corrsponding function is called. Only used by midpoint tau leaping to calculate approximate continuous time derivative.
};

#endif  


