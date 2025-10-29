%{
#include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }
[0-9]+                   { return NUM; }
"="                      { return ASSIGN; }
[+\-*/]                  { return OP; }
";"                      { return SEMICOLON; }
[ \t\n]                  ;   // ignore spaces
.                        { return yytext[0]; }
%%
