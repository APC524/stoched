%{
#include <stdio.h>
#include <iostream>
#include "parser.tab.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
%}
%%
[ \t\n]        { 
                 // ignore tabs and newlines
                 ; }
STOCHED_INPUT  { 
                 // marks the beginning of the input file
                 return PARSER; }
type           { 
                 // declare a data type
                 return TYPE; }
end            { 
                 // mark the end of the data file
                 return END; }
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
.              { 
		 fprintf(stderr, "ERROR: Unrecognized symbol: %s\n", yytext);
                 exit(-1); }
%%