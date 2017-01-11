// This is a function written by Kevin which is called by parser.y
#include <cstdio>
#include <iostream>
#include "model.h"

using namespace std;

bool tauLeapAvail(Model& cModel, string varListStr, string functionStr,
		  int eqnCnt){
  
  // find the name of the variable corresponding to eventCnt
  int begVarName = 0;
  // a,b,c
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
  for (; varListStr[endVarName] == ','; endVarName++){
    if (endVarName == varListStr.length()){
      cout << "the # of functns > # of equations so cant tau leap" << endl;
      return false;
    }
  }
  /*
  // varListStrsubstr = varListStr.substr(end,beg);
  // a,b,c
  // cmp ,b, with beginning of Qstring, ignore whitespace in both.
  // when reach second comma, assert + or - or throw error.
  // probably need to be more cautious about lengths
  int ivs = 0; // counter for the 
  int i...;
  std::string newEqn = $1.copy();
  // need to create varNameList from varString
  //...
  std::string varNameEqn;
  if (isdigit(newEqn[0])){ // assume the case of double +/- var
    //handle this;
    int i = 1;
    for (; !(isdigit(newEqn[i]) || newEqn[i] == '.'); i++){
      ;
    }
    // ignore white space
    if (isspace(newEqn[i])){
      for (; !(isspace(newEqn[i])); i++){
	;
      }
    }
    varNameEqn = newEqn(i);
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
  return false;
}
