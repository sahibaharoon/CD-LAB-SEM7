#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidCondition(char *cond) {
    int len = strlen(cond);
    if (len == 0) return 0;

    for (int i = 0; i < len; i++) {
        char c = cond[i];
        if (!(isalnum(c) || c == '<' || c == '>' || c == '=' || c == '!' || c == '&' || c == '|' || c == ' ')) {
            return 0;
        }
    }
    return 1;
}

int isValidDoWhile(char *str) {
    if (strncmp(str, "do", 2) != 0)
        return 0;

    char *p = str + 2;
    while (isspace(*p)) p++;

    // Case 1: do { ... } while(condition);
    if (*p == '{') {
        char *closingBrace = strchr(p, '}');
        if (!closingBrace)
            return 0;

        char *whilePtr = strstr(closingBrace + 1, "while(");
        if (!whilePtr)
            return 0;

        char *closeParen = strchr(whilePtr, ')');
        if (!closeParen)
            return 0;

        if (*(closeParen + 1) != ';')
            return 0;

        char condition[100];
        strncpy(condition, whilePtr + 6, closeParen - whilePtr - 6);
        condition[closeParen - whilePtr - 6] = '\0';

        return isValidCondition(condition);
    }

    // Case 2: do while(condition);
    else if (strncmp(p, "while(", 6) == 0) {
        char *closeParen = strchr(p, ')');
        if (!closeParen)
            return 0;

        if (*(closeParen + 1) != ';')
            return 0;

        char condition[100];
        strncpy(condition, p + 6, closeParen - p - 6);
        condition[closeParen - p - 6] = '\0';

        return isValidCondition(condition);
    }

    return 0;
}

int main() {
    char input[200];
    printf("Enter a do-while statement: ");
    scanf("%199[^\n]", input);

    if (isValidDoWhile(input))
        printf("✅ Valid do-while statement syntax.\n");
    else
        printf("❌ Invalid do-while statement syntax.\n");

    return 0;
}
