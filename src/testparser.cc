// testparser.cc
#include <iostream>

using namespace std;

//declare the parser method written by flex and bison
int parseFile();

int main(int argc, char *argv[]) {
  cout << "Hello, World" << endl;

  int res = parseFile();
  if (res != 0) {
    fprintf(stderr, "Error: Parser returned %d", res);
  }

  return 0;
}
