%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token IF ELSE ID NUM INC DEC

%%
S   : IFSTMT { printf("Valid if/else statement.\n"); }
;
IFSTMT : IF '(' COND ')'  STMT 
    | IF '(' COND ')' STMT  ELSE STMT 
;
COND: ID '>' ID
    | ID
    | ID '<' ID
    |ID '>' NUM
    | ID '<' NUM
;
STMT : '{' ID INC ';' '}'
    | '{' ID DEC ';' '}'
;
%%

void yyerror(const char *s) {
    printf("Invalid if/else syntax.\n");
}

int main() {
    printf("Enter an if-else statement:\n");
    yyparse();
    return 0;
}
