%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(char *s){
        printf("EOOR OCCURED: %s",s);
    }
    int yylex(void);
%}
%token ID NUMBER LPAR RPAR WHILE LT GT
%%
expr: WHILE LPAR cond RPAR { printf("VALID WHILE LOOP");};
cond:ID LT NUMBER | ID GT NUMBER;

%%
int main(){
    printf("enter the while loop check:");
    yyparse();
    return 0;
}
