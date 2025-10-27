#include <stdio.h>
#include <string.h>

int main() {
    char stack[50], ip[50], opt[10][10][2], ter[10];
    int n, i, j, k, top = 0, row = 0, col = 0;

    // Initialize
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            opt[i][j][0] = '\0';

    printf("Enter number of terminals: ");
    scanf("%d", &n);

    printf("Enter the terminals (as a single string): ");
    scanf("%s", ter);

    printf("\nEnter the operator precedence table values:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter relation for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    // Display the table
    printf("\nOPERATOR PRECEDENCE TABLE:\n\t");
    for (i = 0; i < n; i++) printf("%c\t", ter[i]);
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
        for (j = 0; j < n; j++)
            printf("%c\t", opt[i][j][0] ? opt[i][j][0] : '-');
        printf("\n");
    }

    // Start parsing
    stack[0] = '$';
    stack[1] = '\0';

    printf("\nEnter input string (end with $): ");
    scanf("%s", ip);

    i = 0;
    printf("\n%-15s %-15s %-10s\n", "STACK", "INPUT", "ACTION");
    printf("---------------------------------------------\n");

    while (1) {
        printf("%-15s %-15s ", stack, &ip[i]);

        // Find row, col
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k]) row = k;
            if (ip[i] == ter[k]) col = k;
        }

        // Accept condition
        if (stack[top] == '$' && ip[i] == '$') {
            printf("Accept\n");
            break;
        }

        char relation = opt[row][col][0];

        if (relation == '<' || relation == '=') {
            stack[++top] = ip[i];
            stack[top + 1] = '\0';
            printf("Shift %c\n", ip[i]);
            i++;
        } else if (relation == '>') {
            // Find the nearest < in stack
            int t = top - 1;
            while (t >= 0 && stack[t] != '<' && stack[t] != '$')
                t--;
            if (t >= 0)
                top = t; // reduce to this point
            stack[top + 1] = '\0';
            printf("Reduce\n");
        } else {
            printf("Reject\n");
            break;
        }
    }

    return 0;
}
