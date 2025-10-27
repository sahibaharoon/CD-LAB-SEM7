#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct Production {
    char lhs;
    char rhs[20];
};

int check_reduce(char stack[], int *top, struct Production prods[], int n, char action[]) {
    for (int p = 0; p < n; p++) {
        int rhs_len = strlen(prods[p].rhs);
        if (*top + 1 >= rhs_len) {
            // Check if top of stack ends with RHS
            if (strncmp(stack + (*top - rhs_len + 1), prods[p].rhs, rhs_len) == 0) {
                // Perform reduction
                *top = *top - rhs_len + 1;
                stack[*top] = prods[p].lhs;
                stack[*top + 1] = '\0';
                sprintf(action, "Reduce %c=%s", prods[p].lhs, prods[p].rhs);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    struct Production prods[10];
    int n;

    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar(); // clear newline

    printf("Enter productions (e.g. S = S+S or E = 2E2):\n");
    for (int i = 0; i < n; i++) {
        char line[50];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';

        prods[i].lhs = line[0]; // first char before '='
        char *rhs = strchr(line, '=');
        if (rhs)
            strcpy(prods[i].rhs, rhs + 1);
        else
            strcpy(prods[i].rhs, "");
    }

    char input[MAX], stack[MAX], action[50];
    int i = 0, top = -1, step = 1;

    printf("\nEnter input string: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';

    // Remove spaces
    char cleaned[MAX];
    int j = 0;
    for (int k = 0; input[k]; k++) {
        if (!isspace((unsigned char)input[k]))
            cleaned[j++] = input[k];
    }
    cleaned[j] = '\0';
    strcat(cleaned, "$");

    stack[0] = '\0';

    printf("\n%-5s %-20s %-20s %-25s\n", "Step", "Stack", "Input Buffer", "Action");
    printf("--------------------------------------------------------------------------\n");

    while (1) {
        printf("%-5d %-20s %-20s ", step++, stack, cleaned + i);

        // Accept condition
        if (stack[0] == prods[0].lhs && stack[1] == '\0' && cleaned[i] == '$') {
            printf("Accept\n");
            break;
        }

        // Try reduce
        if (check_reduce(stack, &top, prods, n, action)) {
            printf("%-25s\n", action);
            continue;
        }

        // End of input and no reduction
        if (cleaned[i] == '$') {
            printf("Error: invalid string\n");
            break;
        }

        // Shift
        stack[++top] = cleaned[i++];
        stack[top + 1] = '\0';
        strcpy(action, "Shift");
        printf("%-25s\n", action);
    }

    return 0;
}
