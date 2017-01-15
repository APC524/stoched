/**
 *  @file    testparser.cc
 *  @author  Kevin Griffin (kevinpg@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief Example parsing code
 *
 */

#include <stdio.h>
#include <iostream>
#include "model.h"
#include "event.h"

using namespace std;

/// Declare the parser method written by flex and bison
int parseFile(Model& model, string inputfilename);

/**
 *   @brief Example parsing code 
 *
 *   @return int
 *
 */
int main(int argc, char *argv[]) {
  // validate args
  if (argc < 2) {
    fprintf(stderr, "\nExpected at least 1 argument, got %i \n\n"
	    "USAGE: %s <model file> \n\n"
	    "<model file>: Path to a file "
	    "specifying a stoched model\n\n",
	    argc - 1, argv[0]);
    exit(1);
  }

  Model model;
  int res = parseFile(model, argv[1]);
  if (res != 0) {
    fprintf(stderr, "Error: Parser returned %d", res);
  }
  
  // check if continuous derivative were found and print them
  double stateArray[] = {1, 2};
  if (model.checkTauLeapAvail()){
    for (int i =0; i < model.getVarsCount(); i++) {
      cout << "Continuous derivative for var " << i << " = " 
	   << model.getContDeriv(i,stateArray) << endl;
    }
  }
  return 0;
}
