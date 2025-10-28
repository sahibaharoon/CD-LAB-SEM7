#include <stdio.h>
#include <string.h>

int main() {
    char stack[20], ip[20], opt[10][10][2], ter[10];
    int type[20]; // 0 = operator, 1 = operand
    int i, j, k, n, top = 0, col = -1, row = -1;
    int first_shift_done = 0; // To track the very first shift

    // Initialize arrays
    for (i = 0; i < 20; i++) {
        stack[i] = '\0';
        type[i] = -1;
    }
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            strcpy(opt[i][j], " ");

    printf("Enter the number of terminals: ");
    scanf("%d", &n);

    printf("\nEnter the terminals (no spaces, e.g. +*i$): ");
    scanf("%s", ter);

    printf("\nEnter the operator precedence table values:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            printf("Enter the value for (%c, %c): ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }

    printf("\n--- OPERATOR PRECEDENCE TABLE ---\n\t");
    for (i = 0; i < n; i++) printf("%c\t", ter[i]);
    for (i = 0; i < n; i++) {
        printf("\n%c\t", ter[i]);
        for (j = 0; j < n; j++) printf("%c\t", opt[i][j][0]);
    }

    // Initialize stack
    stack[top] = '$';
    type[top] = 0; // $ is operator

    printf("\n\nEnter the input string (end with $): ");
    scanf("%s", ip);

    i = 0;
    printf("\nSTACK\t\tINPUT STRING\t\tACTION\n");
    for (k = 0; k <= top; k++) printf("%c", stack[k]);
    printf("\t\t");
    for (k = i; k < strlen(ip); k++) printf("%c", ip[k]);
    printf("\t\t");

    while (1) {
        col = row = -1;

        // Find column and row in table
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k]) col = k;
            if (ip[i] == ter[k]) row = k;
        }

        if (col == -1 || row == -1) {
            printf("Reject (invalid symbol)\n");
            break;
        }

        char action = opt[col][row][0];

        // Reject if the very first symbol is not an operand
        if (!first_shift_done && ip[i] != 'i') {
            printf("Reject (expression cannot start with operator)\n");
            break;
        }

        // Accept condition
        if (stack[top] == '$' && ip[i] == '$') {
            printf("Accept\n");
            break;
        }

        // Shift
        if (action == '<' || action == '=') {
            stack[++top] = ip[i];
            type[top] = (ip[i] == 'i') ? 1 : 0; // mark operand/operator
            first_shift_done = 1; // First operand shifted
            printf("Shift\n");
            i++;
        }
        // Reduce
        else if (action == '>') {
            if (top < 1) {
                printf("Reject (invalid reduction)\n");
                break;
            }

            // Find the start of reduction
            int t = top;
            while (t > 0 && stack[t] != '<') t--;
            int start = (t == 0) ? 1 : t + 1;

            // Check for consecutive operands/operators in reduction zone
            int invalid = 0;
            for (int x = start; x <= top; x++) {
                if (x > start && type[x] == type[x - 1]) {
                    invalid = 1;
                    break;
                }
            }
            if (invalid) {
                printf("Reject (invalid operator/operand sequence)\n");
                break;
            }

            // Pop stack until '<'
            while (top > 0 && stack[top] != '<') top--;
            if (top > 0) top--; // pop '<'
            printf("Reduce\n");
        }
        else {
            printf("Reject (invalid table entry)\n");
            break;
        }

        // Print stack and input
        for (k = 0; k <= top; k++) printf("%c", stack[k]);
        printf("\t\t");
        for (k = i; k < strlen(ip); k++) printf("%c", ip[k]);
        printf("\t\t");
    }

    return 0;
}
