%{
#include <stdio.h>
#include <iostream>
#include "parser.tab.h"
using namespace std;
int linecount = 1;
#define YY_DECL extern "C" int yylex()
%}
%%
[ \t]        { 
                 // ignore tabs
                 ; }
STOCHED_INPUT  { 
                 // marks the beginning of the input file
                 return PARSER; }
VARIABLES      { 
                 // marks beginning of variables list
                 return VARIABLES; }
EVENTS         { 
                 // marks beginning of events list
                 return EVENTS; }
RATE           { 
                 // indicates event rate is coming next
                 return RATE; }
end            { 
                 // mark the end of the data file
                 return END; }
\n             {
                 // record line changes and current line number
                 linecount++;
                 return ENDL; }

[0-9]+\.[0-9]+ { 
                 // parser a double
                 yylval.dval = atof(yytext);
                 return DOUBLE; }
[0-9]+         { 
                 // parser an int
                 yylval.ival = atoi(yytext);
                 return INT; }
[a-zA-Z0-9]+   {
                 // parse a string. Need to copy it using strdup
                 yylval.sval = strdup(yytext);
                 return STRING; }
'[a-z \-/=\+A-Z0-9]+'   {
                 // parse an equation as a string but allowing spaces
                 yylval.sval = strdup(yytext);
                 return EQSTRING; }
#.*            {
                 // '#' indicates a comment, so ignore the rest of
                 // the text following # until the next \n
                 ; }
.              { 
		 fprintf(stderr, "ERROR: Unrecognized symbol: %s\n", yytext);
                 exit(-1); }
%%