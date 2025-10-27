%{
#include "ifelse.tab.h"
%}

%%
"if"        { return IF; }
"else"      { return ELSE; }
"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
"<"         {return '>';}
">"         {return '<';}
"++"    {return INC;}
"--"    {return DEC;}
";"         { return ';'; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[0-9]+      { return NUM; }

%%
int yywrap() { return 1; }
