%{
   #include "while.tab.h" 
%}

%%
"while" {return WHILE;}
"(" {return LPAR;}
")" {return RPAR;}
">" {return LT;}
"<" {return GT;}
[0-9]+ {return NUMBER;}
[a-zA-Z]+ {return ID;}

%%
int yywrap(){
    return 1;
}
