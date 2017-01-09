/** 
 *  @file    event.h
 *  @author  Caleb Peckham (peckham@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief APC 524, Final Project - Stoched 
 *
 *  @section DESCRIPTION
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
  
  // Specify name of Event object
  string eventName; 

 private:
  FunctionParser **functionArray_; ///< Array of function parsers 
  FunctionParser rateFunction;     ///< Rate specified by an equation
  double rate_;                    ///< Value of rate equation 
  int eq_count_;                   ///< Number of function parsers

};

#endif  


