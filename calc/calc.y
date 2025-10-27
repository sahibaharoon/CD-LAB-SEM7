
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%%
S : E { printf("Result = %d\n", $1); }
  ;
E : E '+' T     { $$ = $1 + $3; }
  | E '-' T     { $$ = $1 - $3; }
  | T           { $$ = $1; }
  ;

T : T '*' F     { $$ = $1 * $3; }
  | T '/' F     { if($3==0){
                    printf("Error: Division by zero detected.\n");
                        $$=0; 
                }else{
                  $$ = $1 / $3; }}
  | F           { $$ = $1; }
  ;
F : NUMBER      { $$ = $1; }
  ;
%%

int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}
void yyerror(const char *s) {
    printf("Error: %s\n", s);
}
