// testparser.cc
#include <iostream>
#include "model.h"
#include "event.h"


using namespace std;

//declare the parser method written by flex and bison
int parseFile(Model cModel);

int main(int argc, char *argv[]) {
  cout << "Hello, World" << endl;

  Model cModel;
  //"a,b,c"
  int res = parseFile(cModel);
  if (res != 0) {
    fprintf(stderr, "Error: Parser returned %d", res);
  }

  return 0;
}
