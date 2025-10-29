#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidCondition(char *cond) {
    int len = strlen(cond);
    if (len == 0) return 0;

    for (int i = 0; i < len; i++) {
        char c = cond[i];
        if (!(isalnum(c) || c == '<' || c == '>' || c == '=' || c == '!' || c == '&' || c == '|' || c == ' ')) {
            return 0; // invalid character
        }
    }
    return 1;
}

int isValidWhile(char *str) {
    if (strncmp(str, "while(", 6) != 0)
        return 0;

    char *openParen = strchr(str, '(');
    char *closeParen = strrchr(str, ')');

    if (!openParen || !closeParen || closeParen < openParen)
        return 0;

    char condition[100];
    strncpy(condition, openParen + 1, closeParen - openParen - 1);
    condition[closeParen - openParen - 1] = '\0';

    if (!isValidCondition(condition))
        return 0;

    char *after = closeParen + 1;
    while (isspace(*after)) after++;

    if (*after == '\0')
        return 1;
    if (strcmp(after, "{}") == 0)
        return 1;

    return 0;
}

int main() {
    char input[200];
    printf("Enter a while statement: ");
    scanf("%199[^\n]", input);

    if (isValidWhile(input))
        printf("✅ Valid while statement syntax.\n");
    else
        printf("❌ Invalid while statement syntax.\n");

    return 0;
}
