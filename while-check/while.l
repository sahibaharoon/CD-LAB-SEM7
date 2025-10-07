%{
   #include "example.tab.h" 
%}

%%
"while" {return WHILE;}
"do" {return DO;}
"(" {return LPAR;}
")" {return RPAR;}
">" {return LT;}
"{"             { return LBRA; }
"}"             { return RBRA; }
";"             { return SEMI; }
"="             { return ASSIGN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"<" {return GT;}
[0-9]+ {return NUMBER;}
[a-zA-Z]+ {return ID;}
. {return yytext[0];}


%%
int yywrap(){
    return 1;
}
