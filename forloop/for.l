%{
#include "for.tab.h"
%}

%%

"for"       { return FOR; }
"++"        { return INC; }
"--"        { return DEC; }
"=="|"<="|">="|"!="|"<"|">"  { return OPREL; }

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

"="         { return '='; }
";"         { return ';'; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }

[ \t\n]+    ;  // skip whitespace

.           { return yytext[0]; }

%%
int yywrap(){
    return 1;
}
