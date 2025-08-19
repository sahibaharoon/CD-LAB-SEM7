#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Grammar:
// S -> S + S
// S -> S * S
// S -> id

int check_reduce(char stack[], int *top, char action[]) {
    if (*top >= 1 && stack[*top] == 'd' && stack[*top - 1] == 'i') {
        stack[*top - 1] = 'S';   // Reduce id -> S
        (*top)--;
        strcpy(action, "Reduce S->id");
        return 1;
    }
    if (*top >= 2 && stack[*top] == 'S' && stack[*top - 1] == '+' && stack[*top - 2] == 'S') {
        stack[*top - 2] = 'S';   // Reduce S+S -> S
        *top -= 2;
        strcpy(action, "Reduce S->S+S");
        return 1;
    }
    if (*top >= 2 && stack[*top] == 'S' && stack[*top - 1] == '*' && stack[*top - 2] == 'S') {
        stack[*top - 2] = 'S';   // Reduce S*S -> S
        *top -= 2;
        strcpy(action, "Reduce S->S*S");
        return 1;
    }
    return 0;
}

int main() {
    char input[MAX], stack[MAX], action[50];
    int i = 0, top = -1, step = 1;

    printf("Enter input string (e.g., id+id*id): ");
    fgets(input, MAX, stdin);

    // Remove spaces from input
    char cleaned[MAX];
    int j = 0;
    for (int k = 0; input[k]; k++) {
        if (!isspace((unsigned char)input[k]))
            cleaned[j++] = input[k];
    }
    cleaned[j] = '\0';

    strcat(cleaned, "$");  // append end marker

    stack[0] = '\0';  // initialize stack

    printf("\n%-5s %-20s %-20s %-20s\n", "Step", "Stack", "Input Buffer", "Parsing Action");
    printf("--------------------------------------------------------------------------\n");

    while (1) {
        printf("%-5d %-20s %-20s ", step++, stack, cleaned + i);

        // ✅ accept condition
        if (strcmp(stack, "S") == 0 && cleaned[i] == '$') {
            printf("Accept\n");
            break;
        }

        // Try reduce
        if (check_reduce(stack, &top, action)) {
            stack[top + 1] = '\0';
            printf("%-20s\n", action);
            continue;
        }

        // If at end of input and cannot reduce -> error
        if (cleaned[i] == '$') {
            printf("Error: invalid string\n");
            break;
        }

        // Otherwise shift
        stack[++top] = cleaned[i++];
        stack[top + 1] = '\0';
        strcpy(action, "Shift");
        printf("%-20s\n", action);
    }
    return 0;
}
