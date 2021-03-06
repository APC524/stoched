#include "fparser.hh"
#include <iostream>
#include <string>
//#include <stdio.h>
#include <stdlib.h>

//using namespace std;

int main (){
  string function;
  FunctionParser fparser;
  
  fparser.AddConstant("pi", 3.1415926535897932);

  cout << "f(a,b,c) = ";
  getline(cin, function);
  if(cin.fail()){
    return 0;
  }
  int res = fparser.Parse(function, "a,b,c");
  if (res >= 0){
    //std::fprintf(stderr, "Error!\n");

    cout << string(res+7, ' ') << "^\n" << fparser.ErrorMsg() << "\n\n";
    exit(-1);
  }

  double a,b,c;
  cin >> a;
  cin >> b;
  cin >> c;

  double Vars[] = {a, b, c};

  cout << "solution: " << fparser.Eval(Vars) << endl;
  //string;
  //getline(cin, function);
}
