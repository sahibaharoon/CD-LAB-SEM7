
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);                    // 👈 Declare lexer function
int yyerror(const char *s);    
%}

%union {
    char* str;
}

%token <str> IDENTIFIER

%%
stmt: IDENTIFIER '\n' {
    printf("Valid identifier: %s\n", $1);
    free($1);  // good practice
}
;
%%

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int main() {
    printf("Enter input:\n");
    return yyparse();
}

