%{
    #include<stdio.h>
    #include<stdlib.h>
    void yyerror(char *s){
        printf("EOOR OCCURED: %s",s);
    }
    int yylex(void);
%}
%token DO ID PLUS MINUS NUMBER LPAR ASSIGN RPAR WHILE LT GT SEMI LBRA RBRA
%%
expr: DO smt WHILE cond { printf("VALID DO WHILE LOOP");};
smt: LBRA whattodo RBRA ;
whattodo: ID ASSIGN code;
code: ID PLUS NUMBER| NUMBER | ID MINUS NUMBER;
cond:LPAR ope RPAR SEMI ;
ope:  ID LT NUMBER|ID GT NUMBER;

%%
int main(){
    printf("enter the while loop check:");
    yyparse();
    return 0;
}
