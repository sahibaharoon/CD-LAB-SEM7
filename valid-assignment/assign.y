%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}

%token ID NUM ASSIGN OP SEMICOLON

%%
S : STMT SEMICOLON        { printf("Valid assignment statement\n"); }
  ;

STMT : ID ASSIGN EXPR
     ;

EXPR : ID
     | NUM
     | ID OP ID
     | ID OP NUM
     | NUM OP ID
     | NUM OP NUM
     ;
%%

int main() {
    printf("Enter assignment statement:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("Invalid assignment statement\n");
}
