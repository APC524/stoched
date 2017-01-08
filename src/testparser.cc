// testparser.cc
#include <stdio.h>
#include <iostream>
#include "model.h"
#include "event.h"


using namespace std;

//declare the parser method written by flex and bison
int parseFile(Model& model);


int main(int argc, char *argv[]) {
  Model model;
  int res = parseFile(model);
  if (res != 0) {
    fprintf(stderr, "Error: Parser returned %d", res);
  }
  return 0;
}
