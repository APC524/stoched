#include <string>
#include <stdio.h>
#include <iostream>
#include "event.h"
#include "gtest/gtest.h"

class EventTests : public ::testing::Test {
protected:
  virtual void SetUp() {
    event.setRate(rateFunction, variables);
    event.addFunction(function1, variables);
    event.addFunction(function2, variables);
  }

  // virtual void TearDown() {}
  string function1 = "a*b*c";
  string function2 = "a+b+c";
  string variables = "a,b,c";
  string rateFunction = "5*(a+b)";
  double args[3] = {1.0, 2.0, 4.0};
  Event event;
};

TEST_F(EventTests, UseFunction) {
  EXPECT_EQ(8, event.useFunction(0, args));
  EXPECT_EQ(7, event.useFunction(1, args));
}

TEST_F(EventTests, RateFunction) {
  EXPECT_EQ(15, event.getRate(args));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
