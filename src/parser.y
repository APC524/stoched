%{
#include <cstdio>
#include <iostream>
  using namespace std;

  // global varibales that flex defines
  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
 
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
%token TYPE
%token END

// define the data types in the input file
%token <ival> INT
%token <dval> DOUBLE
%token <sval> STRING

%%
// %% demarcates the beginning of the recursive parsing rules
parser:
header template body_section footer { cout << "done with a parser file!" << endl; }
;
header:
PARSER DOUBLE { cout << "reading a parser file version " << $2 << endl; }
;
template:
typelines
;
typelines:
typelines typeline
| typeline
;
typeline:
TYPE STRING { cout << "new defined parser type: " << $2 << endl; }
;
body_section:
body_lines
;
body_lines:
body_lines body_line
| body_line
;
body_line:
INT INT INT INT STRING { cout << "new parser: " << $1 << $2 << $3 << $4 << $5 << endl; }
;
footer:
END
;

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
  cout << "EEK, parse error!  Message: " << s << endl;
  // might as well halt now:
  exit(-1);
}
