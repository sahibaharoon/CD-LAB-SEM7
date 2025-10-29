%{
#include "y.tab.h"
%}

%%
int|float|char         { return TYPE; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
","                    { return COMMA; }
";"                    { return SEMICOLON; }
[ \t\n]                ;       // ignore whitespace
.                      { return yytext[0]; }
%%
