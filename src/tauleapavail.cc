// This is a function written by Kevin which is called by parser.y
#include <cstdio>
#include <iostream>
#include "model.h"

using namespace std;

bool tauLeapAvail(Model& cModel, string varListStr, string functionStr,
		  int eqnCnt){
  
  // cout << "Beginning of tauLeapAvail. Comparing " << varListStr
  // << " with " << functionStr << endl;

  // finding the beginning and end of the variable name in varListStr
  // that corresponds to eqnCnt
  int begVarName = 0;
  for (int commaCnt = 0; commaCnt != eqnCnt; begVarName++){
    if (begVarName == varListStr.length()){
      cout << "\tthe # of functns > # of equations so cant tau leap" << endl;
      return false;
    }
    if (varListStr[begVarName] == ','){
      commaCnt++;
    }
  }
  int endVarName = begVarName;
  for (; !(varListStr[endVarName] == ',' || varListStr[endVarName] == '\0');
       endVarName++){
    if (endVarName == varListStr.length()){
      cout << "\tthe # of functns > # of equations so cant tau leap" << endl;
      return false;
    }
  }

  if (isdigit(functionStr[0])){ // assume the case of double +/- var
    int i = 1;
    for (; (isdigit(functionStr[i]) || functionStr[i] == '.'); i++){
      ;
    }
    // ignore white space
    if (isspace(functionStr[i])){
      for (; isspace(functionStr[i]); i++){
	;
      }
    }
    // expect + or -
    if (i == functionStr.length()){
      cout << "\ttau leaping is available, function is a constant" << endl;
      return true;
    }
    if (!(functionStr[i] == '+' || functionStr[i] == '-')){
      cout << "\ttau leaping not available. was expecting +/-" << endl;
      return false;
    }
    i++;
    if (i == functionStr.length()){
      cerr << "ERROR: invalid function, should not end with +/-" << endl;
      exit(1);
    }
    // ignore white space
    if (isspace(functionStr[i])){
      for (; isspace(functionStr[i]); i++){
	if (i == functionStr.length()){
	  cerr << "ERROR: invalid function, should not end with +/-" << endl;
	  exit(1);
	}
      }
    }
    // compare the variable to the name in the varListStr
    int begFuncVarName = i;
    for (; functionStr[i] != '\0'; i++){
      if (i == functionStr.length() ||
	  i - begFuncVarName + begVarName >= endVarName){
	cout << "\tTau leaping not available: name mismatch" << endl;
	return false;
      }
      // cout << "funcStrChar = " << functionStr[i]
      // << " varListChar = "
      // << varListStr[i - begFuncVarName + begVarName] << endl;
      if (functionStr[i] != varListStr[i - begFuncVarName + begVarName]){
	cout << "\tTau leaping not available since function variable\n"
	  "\tname does not match variable name in the variable list" << endl;
	return false;
      }
    }
    // verify that the end of the varList varaible name was reached
    if (!(varListStr[i - begFuncVarName + begVarName] == ','
	  || varListStr[i - begFuncVarName + begVarName] == '\0')){
      cout << "\tTau leaping not available since function variable\n"
	"\tname is shorter than variable name in the variable list" << endl;
      return false;
    }
  }
  else { // handle the case that the equation begins with nondigit
    int i = 0;
    if (!isalpha(functionStr[i])){
      cout << "\ttau leap is not available. equation begins with\n"
	   << "\tcharacter that is not 0-9, a-z, or A-Z" << endl;
      return false;
    }
    // compare the variable to the name in the varListStr
    int begFuncVarName = i;
    for (; isalpha(functionStr[i]) || isdigit(functionStr[i]); i++){
      if (i == functionStr.length() ||
	  i - begFuncVarName + begVarName >= endVarName){
	cout << "\tTau leaping not available: name mismatch" << endl;
	return false;
      }
      // cout << "\tfuncStrChar = " << functionStr[i]
      // << " varListChar = "
      // << varListStr[i - begFuncVarName + begVarName] << endl;
      if (functionStr[i] != varListStr[i - begFuncVarName + begVarName]){
	cout << "\tTau leaping not available since function variable\n"
	  "\tname does not match variable name in the variable list" << endl;
	return false;
      }
    }
    // verify that the end of the varList varaible name was reached
    if (!(varListStr[i - begFuncVarName + begVarName] == ','
	  || varListStr[i - begFuncVarName + begVarName] == '\0')){
      cout << "\tTau leaping not available since function variable\n"
	"\tname is shorter than variable name in the variable list" << endl;
      return false;
    }

    // the variable names match, but verify that the rest of the
    // function string is compatible with tau leaping

    // ignore white space
    if (isspace(functionStr[i])){
      for (; isspace(functionStr[i]); i++){
	;
      }
    }
    // expect + or -
    if (i == functionStr.length()){
      cout << "\ttau leaping is available, function is constant" << endl;
      return true;
    }
    if (!(functionStr[i] == '+' || functionStr[i] == '-')){
      cout << "\ttau leaping not available. was expecting +/-" << endl;
      return false;
    }
    i++;
    if (i == functionStr.length()){
      cerr << "ERROR: invalid function. should not end with +/-" << endl;
      exit(1);
    }
    // ignore white space
    if (isspace(functionStr[i])){
      for (; isspace(functionStr[i]); i++){
	;
      }
    }
    if (i == functionStr.length()){
      cerr << "ERROR: invalid function. should not end with +/-" << endl;
      exit(1);
    }
    if (!(isdigit(functionStr[i]) || functionStr[i] == '.')){
      cout << "\ttau leaping not available. was expecting a double" << endl;
      return false;
    }
    // expect a double
    for (; (isdigit(functionStr[i]) || functionStr[i] == '.'); i++){
      ;
    }
    // expect a \0 character
    if (functionStr[i] != '\0'){
      cout << "\ttau leaping not available. was expecting end of function"
	   << endl;
      return false;
    }
  }
  cout << "\ttau leap is available" << endl;
  return true;
}
