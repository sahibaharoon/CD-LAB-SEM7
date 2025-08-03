
%{
#include "var.tab.h"
#include <string.h>
int yyerror(const char *s);
%}

IDENTIFIER    [a-zA-Z][a-zA-Z0-9]*

%%

{IDENTIFIER} {
    yylval.str = strdup(yytext);
    return IDENTIFIER;
}

\n      { return '\n'; }
.       { yyerror("Invalid input"); }

%%

int yywrap() {
    return 1;
}