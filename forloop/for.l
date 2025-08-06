%{
#include "for.tab.h"
int yylex(void);
void yyerror(const char *s);
%}

alpha   [A-Za-z]
digit   [0-9]

%%

[ \t\n]+                  ;  // Ignore whitespace
for                       return FOR;
{digit}+                  return NUM;
{alpha}({alpha}|{digit})* return ID;
"<="                       return LE;
">="                       return GE;
"++"            			return INCR;
"--"            			return DECR;
"=="                       return EQ;
"!="                       return NE;
"||"                       return OR;
"&&"                       return AND;
"="                        return '=';
"<"                        return '<';
">"                        return '>';
"\\+"                       return '+';
"-"                        return '-';
"\\*"                       return '*';
"/"                        return '/';
"\\("                       return '(';
"\\)"                       return ')';
"\\{"                       return '{';
"\\}"                       return '}';
";"                        return ';';
.                          return yytext[0];

%%

