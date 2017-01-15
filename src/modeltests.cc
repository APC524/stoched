/**
 *  @file    modeltests.cc
 *  @author  Caleb Peckham (peckham@princeton.edu)
 *  @date    12/11/16  
 *  @version 1.0 
 *  
 *  @brief   Test usage of Model class
 *
 */

#include <string>
#include <stdio.h>
#include <iostream>
#include "model.h"
#include "gtest/gtest.h"

class ModelTests : public ::testing::Test {
protected:
  virtual void SetUp() {
    model.addVars(variables);

    model.addEvent(rateFunction1);
    model.addEventFct(0, function1A);
    model.addEventFct(0, function1B);
    model.addEventFct(0, function1C);

    model.addEvent(rateFunction2);
    model.addEventFct(1, function2A);
    model.addEventFct(1, function2B);
    model.addEventFct(1, function2C);

  }

  // virtual void TearDown() {}
  string variables = "a,b,c";
  double args[3] = {1.0, 2.0, 4.0};
  double rateArray[2] = {0.0, 0.0};

  string function1A = "a*b*c";
  string function1B = "a+b+c";
  string function1C = "c*b-a";
  string rateFunction1 = "5*(a+b)";

  string function2A = "a+b*c";
  string function2B = "a*b-c";
  string function2C = "(a-b)*c";
  string rateFunction2 = "c*(a+b)";

  Model model;

};

TEST_F(ModelTests, UseEventFunction) {
  EXPECT_EQ(8, model.useEventFct(0, 0, args));
  EXPECT_EQ(7, model.useEventFct(0, 1, args));
  EXPECT_EQ(7, model.useEventFct(0, 2, args));
 
  EXPECT_EQ(9, model.useEventFct(1, 0, args));
  EXPECT_EQ(-2, model.useEventFct(1, 1, args));
  EXPECT_EQ(-4, model.useEventFct(1, 2, args));
}

TEST_F(ModelTests, EventRateFunction) {
  EXPECT_EQ(15, model.getEventRate(0, args));
  EXPECT_EQ(12, model.getEventRate(1, args));
}

TEST_F(ModelTests, UpdateRateFunction) {
  model.updateRates(args, rateArray);
  EXPECT_EQ(15, rateArray[0]);
  EXPECT_EQ(12, rateArray[1]);
}

TEST_F(ModelTests, UpdateStateArray) {
  model.updateState(0, args);
  EXPECT_EQ(8, args[0]);
  EXPECT_EQ(7, args[1]);
  EXPECT_EQ(7, args[2]);

  model.updateState(1, args);
  EXPECT_EQ(57, args[0]);
  EXPECT_EQ(49, args[1]);
  EXPECT_EQ(7, args[2]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
