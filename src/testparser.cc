/**
 *  @file    testparser.cc
 *  @author  Kevin Griffin (kevinpg@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief APC 524, Final Project - Stoched
 *
 *  @section DESCRIPTION
 *  
 */

#include <iostream>
#include "model.h"
#include "event.h"

using namespace std;

/// Eeclare the parser method written by flex and bison
int parseFile(Model& model);

/**
 *   @brief Example parsing code 
 *
 *   @return int
 *
 */

int main(int argc, char *argv[]) {
  cout << "Hello, World" << endl;

  Model model;
  //"a,b,c"
  int res = parseFile(model);
  if (res != 0) {
    fprintf(stderr, "Error: Parser returned %d", res);
  }

  // test that the Model was initialized by the parser properly
  double args[3] = {1.0, 2.0, 4.0};
  //double rateArray[2] = {0.0, 0.0};
  
  cout << "Function 1A: a*b*c = " << model.useEventFct(0, 0, args) << endl;  
  cout << "Function 1B: a+b+c = " << model.useEventFct(0, 1, args) << endl;
  cout << "Function 1C: c*b-a = " << model.useEventFct(0, 2, args) << endl;

  cout << "Function 2A: a+b*c = " << model.useEventFct(1, 0, args) << endl;
  cout << "Function 2B: a*b-c = " << model.useEventFct(1, 1, args) << endl;
  cout << "Function 2C: (a-b)*c = " << model.useEventFct(1, 2, args) << endl;

  cout << "Rate Function 1: 5*(a+b) = " << model.getEventRate(0, args) << endl;
  cout << "Rate Function 2: c*(a+b) = " << model.getEventRate(1, args) << endl;

  return 0;
}
