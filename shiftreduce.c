#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int n;

struct production {
    char lhs;
    char rhs[10];
};

int reduce(char stack[], int *top, char lookahead, char action[], struct production p[], int num_productions) {
    for (int i = 0; i < num_productions; i++) {
        int rhslen = strlen(p[i].rhs);
        if (*top + 1 >= rhslen) {
            if (strncmp(stack + (*top - rhslen + 1), p[i].rhs, rhslen) == 0) {
                if (p[i].lhs == 'E' && (lookahead == '*' || lookahead == '/')) {
                    continue;
                }
                *top = *top - rhslen + 1;
                stack[*top] = p[i].lhs;
                stack[*top + 1] = '\0';
                sprintf(action, "Reduce %c->%s", p[i].lhs, p[i].rhs);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    struct production p[10];
    setbuf(stdout, NULL);

    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 10) {
        fprintf(stderr, "Invalid number of productions.\n");
        return 1;
    }

    printf("Enter productions (format: A=xyz):\n");
    for (int i = 0; i < n; i++) {
        char line[50];
        if (scanf("%49s", line) != 1) {
            fprintf(stderr, "Error reading production.\n");
            return 1;
        }
        p[i].lhs = line[0];
        char *rhs = strchr(line, '=');
        if (!rhs) {
            fprintf(stderr, "Invalid production format. Use A=xyz.\n");
            return 1;
        }
        rhs++;
        strncpy(p[i].rhs, rhs, 9);
        p[i].rhs[9] = '\0';
    }

    char input[30];
    printf("ENTER THE STRING TO CHECK: ");
    if (scanf("%29s", input) != 1) {
        fprintf(stderr, "Error reading input string.\n");
        return 1;
    }
    strcat(input, "$");

    printf("\n%-5s %-20s %-20s %-25s\n", "Step", "Stack", "Input Buffer", "Action");
    printf("---------------------------------------------------------------------\n");

    int step = 1, i = 0, top = -1;
    char stack[30], action[30];
    stack[0] = '\0';

    while (1) {
        printf("%-5d %-20s %-20s ", step++, stack, input + i);
        if (input[i] == '$' && stack[0] == p[0].lhs && stack[1] == '\0') {
            printf("ACCEPT\n");
            break;
        }
        if (reduce(stack, &top, input[i], action, p, n)) {
            printf("%s\n", action);
            continue;
        }
        if (input[i] == '$') {
            printf("ERROR: No valid reduction possible at end of input.\n");
            break;
        }
        stack[++top] = input[i];
        i++;
        stack[top + 1] = '\0';
        printf("SHIFT\n");
    }
    return 0;
}
