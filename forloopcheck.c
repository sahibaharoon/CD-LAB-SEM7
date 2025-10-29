#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidForLoop(char *str) {
    // Basic pattern: for ( init ; condition ; increment )
    if (strncmp(str, "for(", 4) != 0)  // must start with "for("
        return 0;

    int len = strlen(str);
    if (str[len - 1] != ')')  // must end with ')'
        return 0;

    char inside[100];
    strncpy(inside, str + 4, len - 5); // copy content inside ( )
    inside[len - 5] = '\0';

    // Count number of semicolons
    int semicolons = 0;
    for (int i = 0; i < strlen(inside); i++)
        if (inside[i] == ';')
            semicolons++;

    if (semicolons != 2)
        return 0;

    return 1;
}

int main() {
    char input[100];
    printf("Enter a for loop header (e.g. for(i=0;i<n;i++)): ");
    scanf("%[^\n]", input);

    if (isValidForLoop(input))
        printf("✅ Valid for loop syntax.\n");
    else
        printf("❌ Invalid for loop syntax.\n");

    return 0;
}



//WITH BRACES VERSION 




#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidForLoop(char str[]) {
    int len = strlen(str);

    // Must start with "for("
    if (len < 6 || str[0] != 'f' || str[1] != 'o' || str[2] != 'r' || str[3] != '(')
        return 0;

    // Find the closing parenthesis ')'
    int closeIndex = -1;
    for (int i = 4; i < len; i++) {
        if (str[i] == ')') {
            closeIndex = i;
            break;
        }
    }

    if (closeIndex == -1)
        return 0; // no closing ')'

    // Count semicolons between '(' and ')'
    int semicolons = 0;
    for (int i = 4; i < closeIndex; i++) {
        if (str[i] == ';')
            semicolons++;
    }

    if (semicolons != 2)
        return 0;

    // Check what comes after ')'
    int hasOpeningBrace = 0, hasClosingBrace = 0;

    for (int i = closeIndex + 1; i < len; i++) {
        if (isspace(str[i]))
            continue;
        if (str[i] == '{')
            hasOpeningBrace = 1;
        else if (str[i] == '}')
            hasClosingBrace = 1;
    }

    // Valid if: 
    // 1️⃣ just ends after ')' OR 
    // 2️⃣ contains both '{' and '}'
    if (hasOpeningBrace && hasClosingBrace)
        return 1;
    else if (!hasOpeningBrace && !hasClosingBrace)
        return 1;
    else
        return 0; // mismatched braces
}

int main() {
    char input[200];
    printf("Enter a for loop (you can include braces):\n");
    scanf("%[^\n]", input);

    if (isValidForLoop(input))
        printf("✅ Valid for loop syntax.\n");
    else
        printf("❌ Invalid for loop syntax.\n");

    return 0;
}

