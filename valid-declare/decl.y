%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}

%token TYPE ID COMMA SEMICOLON

%%
S : D SEMICOLON           { printf("Valid declaration\n"); }
  ;

D : TYPE VLIST            ;

VLIST : ID
      | VLIST COMMA ID
      ;
%%

int main() {
    printf("Enter declaration statement:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("Invalid declaration\n");
}
