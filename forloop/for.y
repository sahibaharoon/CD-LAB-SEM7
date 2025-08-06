%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s) { printf("Syntax Error: %s\n", s); exit(1); }

%}

%token ID NUM FOR LE GE EQ NE OR AND INCR DECR
%right '='
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%right UMINUS
%left '!'



%%

S       : ST { printf("Input accepted\n"); exit(0); } ;

ST      : FOR '(' E ';' E ';' E ')' DEF ;

DEF     : '{' BODY '}'
        | E ';'
        | ST
        | 
        ;

BODY    : BODY BODY
        | E ';'
        | ST
        | 
        ;

E       : ID '=' E
        | E '+' E
        | E '-' E
        | E '*' E
        | E '/' E
        | E '<' E
        | E '>' E
        | E LE E
        | E GE E
        | E EQ E
        | E NE E
        | E OR E
        | E AND E
         | ID INCR
  | ID DECR
        | NUM
        | ID
        ;


%%



int main() {
    printf("Enter a for loop:\n");
    yyparse();
    return 0;
}

