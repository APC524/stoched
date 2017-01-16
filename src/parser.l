/** 
 *  @file    parser.l
 *  @author  Kevin Griffin (kevinpg@princeton.edu)
 *  @date    12/6/16  
 *  @version 1.0 
 *  
 *  @brief APC 524, Final Project - Stoched 
 *
 *  @section DESCRIPTION
 *  
 */


%option noyywrap

%{
#include <stdio.h>
#include <iostream>
#include "parser.bison.hh"

using namespace std;
int linecount = 1;
#define YY_DECL extern "C" int yylex()

%}
%%
[ \t]          { 
                 // ignore tabs
                 ; }
SETUP_VARS     { 
                 // marks beginning of file and is followed by variables string
                 return SETUP_VARS; }
EVENT          { 
                 // marks beginning of event line
                 return EVENT; }
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
\"[a-z \. , ( ) \+ \- \* / A-Z0-9]+\"   {
                 // parse a string beginning and ending with quotes. string may
                 // contain a-z A-Z 0-9 and the symbols ,+-*./=() and spaces 
                 yylval.sval = strdup(yytext);
                 int len = 0;
                 while(yylval.sval[len] != '\0'){
                 len++;
                 }
                 // delete the trailing quote from the string
                 yylval.sval[len-1] = '\0';
                 // delete leading quote from the string
                 yylval.sval++;
                 return QSTRING; }
#.*            {
                 // '#' indicates a comment, so ignore the rest of
                 // the text following # until the next \n
                 ; }
.              { 
		 fprintf(stderr, "ERROR: Unrecognized symbol: %s\n", yytext);
                 exit(-1); }
%%
// [a-zA-Z0-9]+   {
//                 // parse a string containing only letters and numbers
//                 yylval.sval = strdup(yytext);
//                 return STRING; }
