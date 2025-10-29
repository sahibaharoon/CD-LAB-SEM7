#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to check if "if" syntax is valid
int isValidIfElse(char str[]) {
    int len = strlen(str);
    
    // Trim leading spaces
    int start = 0;
    while (isspace(str[start])) start++;

    // Must start with "if("
    if (str[start] != 'i' || str[start + 1] != 'f' || str[start + 2] != '(')
        return 0;

    // Find matching ')'
    int closeParen = -1;
    for (int i = start + 3; i < len; i++) {
        if (str[i] == ')') {
            closeParen = i;
            break;
        }
    }
    if (closeParen == -1)
        return 0; // No closing parenthesis

    // After ')', expect '{'
    int openBrace = -1, closeBrace = -1;
    for (int i = closeParen + 1; i < len; i++) {
        if (isspace(str[i])) continue;
        if (str[i] == '{') {
            openBrace = i;
            break;
        }
    }
    if (openBrace == -1)
        return 0; // Missing opening brace

    // Find closing '}'
    for (int i = openBrace + 1; i < len; i++) {
        if (str[i] == '}') {
            closeBrace = i;
            break;
        }
    }
    if (closeBrace == -1)
        return 0; // Missing closing brace

    // Check if "else" exists after '}'
    int hasElse = 0, elseOpen = -1, elseClose = -1;
    for (int i = closeBrace + 1; i < len; i++) {
        if (isspace(str[i])) continue;

        // Check for "else"
        if (strncmp(&str[i], "else", 4) == 0) {
            hasElse = 1;

            // Expect '{' after else
            for (int j = i + 4; j < len; j++) {
                if (isspace(str[j])) continue;
                if (str[j] == '{') {
                    elseOpen = j;
                    break;
                }
            }

            // Find closing '}'
            if (elseOpen != -1) {
                for (int j = elseOpen + 1; j < len; j++) {
                    if (str[j] == '}') {
                        elseClose = j;
                        break;
                    }
                }
            }

            // Missing braces in else block
            if (elseOpen == -1 || elseClose == -1)
                return 0;
        }
        break; // only one else allowed
    }

    // If only if-block or if-else block is valid
    return 1;
}

int main() {
    char input[300];
    printf("Enter an if or if-else statement (single line):\n");
    scanf("%[^\n]", input);

    if (isValidIfElse(input))
        printf("✅ Valid if/else syntax.\n");
    else
        printf("❌ Invalid if/else syntax.\n");

    return 0;
}
