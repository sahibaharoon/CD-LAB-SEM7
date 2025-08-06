%{
#include "parser.tab.h"
%}

%%
[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[ \t]+      ;      // ignore spaces and tabs
\n          { return '\n'; }  // signal end of expression
.           { return yytext[0]; }

%%

int yywrap() {
    return 1; // no more input
}

