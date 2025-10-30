#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][10] = {"int", "float", "if", "else", "while", "return", "for"};
int n_keywords = 7;

int isKeyword(char *word) {
    for (int i = 0; i < n_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char input[200];
    printf("Enter the input string: ");
    fgets(input, sizeof(input), stdin);  // Read full line input

    int i = 0;
    char token[50];
    int t_index = 0;

    printf("\nTOKENS:\n");
    printf("-----------------------------\n");

    while (input[i] != '\0') {
        // Skip whitespaces
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // Identifiers or keywords
        if (isalpha(input[i])) {
            t_index = 0;
            while (isalnum(input[i])) {
                token[t_index++] = input[i++];
            }
            token[t_index] = '\0';

            if (isKeyword(token))
                printf("<KEYWORD, %s>\n", token);
            else
                printf("<IDENTIFIER, %s>\n", token);
        }

        // Numbers
        else if (isdigit(input[i])) {
            t_index = 0;
            while (isdigit(input[i])) {
                token[t_index++] = input[i++];
            }
            token[t_index] = '\0';
            printf("<NUMBER, %s>\n", token);
        }

        // Operators and punctuation
        else {
            printf("<OPERATOR, %c>\n", input[i]);
            i++;
        }
    }

    printf("-----------------------------\n");
    return 0;
}
