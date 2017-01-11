/** 
 *  @file    parser.y
 *  @author  Kevin Griffin (kevinpg@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief APC 524, Final Project - Stoched 
 *
 *  @section DESCRIPTION
 *  
 */

%{

#include <cstdio>
#include <iostream>
#include "model.h"
#include "event.h"

  using namespace std;

  // global variables that flex defines
  extern "C" int yylex();
  extern "C" int yyparse(Model& cModel, int eventCnt, int eqnCnt);
  extern "C" FILE *yyin;
  extern int linecount;
 
  // declare error function
  void yyerror(Model& cModel, int eventCnt, int eqnCnt, const char *s);
  // declare a function to check if tau leaping is available
  bool tauLeapAvail(Model& cModel, string varListStr, string functionStr,
		  int eqnCnt);
  %}
// flex returns a token as a yystype. Bison will store this in a union
// containing the different data types.
%union {
  int ival;
  float dval;
  char *sval;
}

// define the keywords
%token SETUP_VARS
%token EVENT
%token RATE
%token END
%token ENDL
%token COMMENT

// define the data types in the input file
%token <ival> INT
%token <dval> DOUBLE
%token <sval> QSTRING

 // input argument(s) to the parser function
%parse-param {Model& cModel}
%parse-param {int eventCnt}
%parse-param {int eqnCnt}

%%
// %% demarcates the beginning of the recursive parsing rules
parser:
{  // cout << "set eventCnt = 0" << endl; 
   eventCnt = 0; 
   // cout << "set eqnCnt = 0" << endl;
   eqnCnt = 0; 
}
vars_line event_lines footer {
  cout << "done with a parser file!" << endl;
}
;
vars_line:
SETUP_VARS QSTRING ENDLS {
  cout << "Variables: " << $2 << endl;
  cModel.addVars($2);
}
;
event_lines:
event_lines event_line
| event_line
;
event_line:
EVENT RATE QSTRING
{ cout << "Adding new event. eventCnt = " << eventCnt << endl;
  cout << "Setting rate = " << $3 << endl;
  cModel.addEvent($3);
} equations_list {
  //cout << "increment eventCnt" << endl;
  eventCnt++;
  //cout << "new val of eventCnt = " << eventCnt << endl;
  eqnCnt = 0;
  //cout << "reset eqnCnt to " << eqnCnt << endl;
  } ENDLS {
    cout << "End of event" << endl;
    }
;
equations_list:
equations_list QSTRING 
{ cout << "Adding new equation: " << $2 << " "; 
  cout << "eqnCnt = " << eqnCnt<< endl;
  cModel.addEventFct(eventCnt, $2);
  // check if this new equation is compatible with tau leaping
  if (!tauLeapAvail(cModel, cModel.getVarsString(), $2, eqnCnt)){
    cModel.setTauLeapFalse();
  }
  eqnCnt++;
}
| QSTRING 
{ cout << "Adding new equation: " << $1 << " "; 
  cout << "eqnCnt = " << eqnCnt<< endl;
  cModel.addEventFct(eventCnt, $1); 
  // check if this new equation is compatible with tau leaping
  if (!tauLeapAvail(cModel, cModel.getVarsString(), $1, eqnCnt)){
    cModel.setTauLeapFalse();
  }
  eqnCnt++;
}
;
footer:
END ENDLS
;
ENDLS:
ENDLS ENDL
| ENDL ;

%%

int parseFile(Model& cModel, string inputfile) {
  // set the input file
  //string inputfile = "example.parser.in";
  FILE *myfile = fopen(inputfile.c_str(), "r");
  // check that the file is valid
  if (!myfile) {
    cout << "ERROR opening the file named: " << inputfile << endl;
    return -1;
  }
  // set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;

  // parse through the input until there is no more:
  do {
    cout << "Begin parsing file named: " << inputfile << endl;
    int eventCnt = 0;
    int eqnCnt = 0;
    yyparse(cModel, eventCnt, eqnCnt);
  } while (!feof(yyin));
  return 0;
}

void yyerror(Model& cModel, int eventCnt, int eqnCnt, const char *s) {
  cout << "ERROR: Parser error on line " << linecount << ". Message: " << s << endl;
  exit(-1);
}
