%{
    #include <stdio.h>
    #include <string.h>

    char prefix[5];  // 4 characters + '\0'
%}

%%
[a-zA-Z]+ {
    if (strstr(yytext, prefix)) {
        printf("Rejected: '%s' contains '%s'\n", yytext, prefix);
    } else {
        printf("Accepted: '%s'\n", yytext);
    }
}

\n   { /* ignore newline */ }
.    { /* ignore other characters */ }
%%

int main() {
    printf("Enter your name: ");
    scanf("%s", prefix);
    prefix[4] = '\0';  // Take only first 4 characters
    printf("Now enter strings to test (Ctrl+D to end):\n");
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}