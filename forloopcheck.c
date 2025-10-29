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
