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
int parseFile(Model& model);

/**
 *   @brief Example parsing code 
 *
 *   @return int
 *
 */
int main(int argc, char *argv[]) {
  Model model;
  int res = parseFile(model);
  if (res != 0) {
    fprintf(stderr, "Error: Parser returned %d", res);
  }
  return 0;
}
