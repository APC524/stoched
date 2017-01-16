/**
 *  @file    parsertests.cc
 *  @author  Caleb Peckham (peckham@princeton.edu)
 *  @date    1/12/17  
 *  @version 1.0 
 *  
 *  @brief Example parsing code
 *
 */

#include <string>
#include <stdio.h>
#include <iostream>
#include "model.h"
#include "event.h"
#include "gtest/gtest.h"

using namespace std;

// Declare the parser method written by flex and bison
int parseFile(Model& model, string inputfilename);

class ParserTests : public ::testing::Test {
protected:
  virtual void SetUp() {

  }
  // virtual void TearDown() {}
  Model model;
};


TEST_F(ParserTests, ParserReturn) {
  EXPECT_EQ(0, parseFile(model, "example.parser.in"));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
