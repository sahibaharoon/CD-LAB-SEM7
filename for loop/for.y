%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token ID NUMBER FOR OPREL INC DEC

%%

stmt:
    FOR '(' expr_stmt expr_stmt expr ')' block { printf("Valid FOR loop syntax\n"); }
    ;

expr_stmt:
    expr ';'
    ;

expr:
    ID '=' expr
    | ID OPREL expr
    | ID
    | NUMBER
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | INC ID
    | ID INC
    | DEC ID
    | ID DEC
    ;

block:
    '{' '}'
    | '{' stmt_list '}'
    ;

stmt_list:
    stmt
    | stmt_list stmt
    ;

%%

void yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
}

int main() {
    printf("Enter a FOR loop:\n");
    yyparse();
    return 0;
}
