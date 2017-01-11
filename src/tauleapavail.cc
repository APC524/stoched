// This is a function written by Kevin which is called by parser.y
#include <cstdio>
#include <iostream>
#include "model.h"

using namespace std;

bool tauLeapAvail(Model& cModel, string varListStr, string functionStr,
		  int eqnCnt){
  
  cout << "Beginning of tauLeapAvail. Comparing " << varListStr
       << " with " << functionStr << endl;
  // extract the name of variable in varListStr that corresponds to eqnCnt
  int begVarName = 0;
  for (int commaCnt = 0; commaCnt == eqnCnt; begVarName++){
    if (begVarName == varListStr.length()){
      cout << "the # of functns > # of equations so cant tau leap" << endl;
      return false;
    }
    if (varListStr[begVarName] == ','){
      commaCnt++;
    }
  }
  int endVarName = begVarName;
  for (; varListStr[endVarName] == ',' || varListStr[endVarName] == '\0';
       endVarName++){
    if (endVarName == varListStr.length()){
      cout << "the # of functns > # of equations so cant tau leap" << endl;
      return false;
    }
  }
  // now I have two ints that demarcate beg and end of var, possibly containing
  //whitespace on either side.
  //... do something with these like copy into a sub string?
  /*
  // varListStrsubstr = varListStr.substr(end,beg);
  // a,b,c
  // cmp ,b, with beginning of Qstring, ignore whitespace in both.
  // when reach second comma, assert + or - or throw error.
  // probably need to be more cautious about lengths
  int ivs = 0; // counter for the 
  int i...;
  std::string functionStr = $1.copy();
  // need to create varNameList from varString
  //...
  std::string varNameEqn;
  */
  if (isdigit(functionStr[0])){ // assume the case of double +/- var
    //handle this;
    int i = 1;
    for (; !(isdigit(functionStr[i]) || functionStr[i] == '.'); i++){
      if (i == functionStr.length()){
	cout << "tau leaping not available, function is a constant" << endl;
	return false;
      }
    }
    // ignore white space
    if (isspace(functionStr[i])){
      for (; !(isspace(functionStr[i])); i++){
	if (i == functionStr.length()){
	  cout << "tau leaping not available, function is a constant" << endl;
	  return false;
	}
      }
    }
    // expect + or -
    if (i == functionStr.length()){
      cout << "tau leaping not available, function is a constant" << endl;
      return false;
    }
    if (!(functionStr[i] == '+' || functionStr[i] == '-')){
      cout << "tau leaping not available, function is a constant" << endl;
      return false;
    }
    i++;
    if (i == functionStr.length()){
      cerr << "invalid function, should not end with +/-" << endl;
      exit(1);
    }
    // ignore white space
    if (isspace(functionStr[i])){
      for (; !(isspace(functionStr[i])); i++){
	if (i == functionStr.length()){
	  cerr << "invalid function, should not end with +/-" << endl;
	  exit(1);
	}
      }
    }
    // compare the variable to the name in the varListStr
    int begFuncVarName = i;
    for (; functionStr[i] != '\0'; i++){
      if (i == functionStr.length() ||
	  i - begFuncVarName + begVarName >= endVarName){
	cout << "Tau leaping not available: name mismatch";
	return false;
      }
      if (functionStr[i - begFuncVarName] != varListStr[i-begVarName]){
	cout << "Tau leaping not available since does function variable name"
	  "does not match variable name in the variable list" << endl;
	return false;
      }
    }
    return true;
  }
  else {
    //handle other case !!!!!!!!!
    cout << "this case is not implemented yet" << endl;
    return false; // this is temporary
  }
    /*    varNameEqn = functionStr(i);
    if (varNameList.compare(varNameEqn)){
      // mark as TAU_LEAP_AVAIL = true;
      //...
    }
  }
  else { // assume case of var +/- double
    // handle this;
    // invloves stepping through and verifying +/- and double.
    // if it is violated, break
    // mark as TAU_LEAP_AVAIL = true;
  }
  
  int token1Len = 0;
  for (; QSTRING[token1Len] == '\s' || QSTRING[token1Len] == '\t'; token1Len++){
  }
  
  cout << "The euler compatible var begins at position " << i << endl;
  // find end of var (next , or \0) and put it in a string.
  // string cmp beginning of it with the t
  // ...
  */
}
