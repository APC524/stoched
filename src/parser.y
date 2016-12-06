%{
#include <cstdio>
#include <iostream>
#include "event.h"

  using namespace std;

  // global varibales that flex defines
  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern int linecount;
 
  void yyerror(const char *s); // declare the error function
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

%%
// %% demarcates the beginning of the recursive parsing rules
parser:
vars_line event_lines footer { cout << "done with a parser file!"
						   << endl; }
;
vars_line:
SETUP_VARS QSTRING ENDLS { cout << "Beginning of input file\nvariables: " << $2 << endl; }
;
event_lines:
event_lines event_line
| event_line
;
event_line:
EVENT equations_list RATE QSTRING ENDLS {   
  cout << "rate= " << $4 << endl; 
}
;
equations_list:
equations_list QSTRING { cout << $2 << " "; }
| QSTRING { cout << $1 << " "; }
;
footer:
END ENDLS
;
ENDLS:
ENDLS ENDL
| ENDL ;

%%

int parseFile() {
  // set the input file
  string inputfile = "example.parser.in";
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
    yyparse();
  } while (!feof(yyin));
  return 0;
}

void yyerror(const char *s) {
  cout << "ERROR: Parser error on line " << linecount << ". Message: " << s << endl;
  exit(-1);
}
