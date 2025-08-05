%{
#include "y.tab.h"
%}

%%

[0-9]+    { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n]+  ;     // ignore whitespace
.         { return yytext[0]; }

%%
