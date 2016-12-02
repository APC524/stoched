%{
#include <cstdio>
#include <iostream>
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
%token PARSER
%token VARIABLES
%token EVENTS
%token RATE
%token END
%token ENDL
%token COMMENT

// define the data types in the input file
%token <ival> INT
%token <dval> DOUBLE
%token <sval> STRING
%token <sval> EQSTRING

%%
// %% demarcates the beginning of the recursive parsing rules
parser:
header vars_line events_line body_section footer { cout << "done with a parser file!"
						   << endl; }
;
header:
PARSER DOUBLE ENDLS { cout << "reading a parser file version " << $2 << endl; }
;
vars_line:
VARIABLES variable_list ENDLS { cout << "end of variable list" << endl; }
;
variable_list:
variable_list STRING { cout << "reading a variable: " << $2 << endl; }
| STRING { cout << "reading a variable: " << $1 << endl; }
;
events_line:
EVENTS events_list ENDLS { cout << "end of events list" << endl; }
;
events_list:
events_list STRING { cout << "reading an event: " << $2 << endl; }
| STRING { cout << "reading an event: " << $1 << endl; }
;
body_section:
body_lines
;
body_lines:
body_lines body_line
| body_line
;
body_line:
STRING equations_list RATE DOUBLE ENDLS { cout << "rate=" << $4 << endl; }
;
equations_list:
equations_list EQSTRING { cout << $2 << " "; }
| EQSTRING { cout << $1 << " "; }
;
footer:
END ENDLS
;
ENDLS:
ENDLS ENDL
| ENDL ;

%%

int main(int, char**) {
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
  
}

void yyerror(const char *s) {
  cout << "ERROR: Parser error on line " << linecount << ". Message: " << s << endl;
  exit(-1);
}
