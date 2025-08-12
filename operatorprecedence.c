#include <stdio.h>
#include <string.h>

int main() {
    char stack[20], ip[20], opt[10][10][2], ter[10];
    int i, j, k, n, top = 0, row = 0, col = 0;

    // Initialize
    for (i = 0; i < 20; i++) stack[i] = '\0';
    for (i = 0; i < 20; i++) ip[i] = '\0';
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            opt[i][j][0] = '\0';

    printf("Enter the number of terminals: ");
    scanf("%d", &n);

    printf("Enter the terminals: ");
    scanf("%s", ter);

    printf("\nEnter the operator precedence table values:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    printf("\nOPERATOR PRECEDENCE TABLE:\n\t");
    for (i = 0; i < n; i++) printf("%c\t", ter[i]);
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
        for (j = 0; j < n; j++) printf("%c\t", opt[i][j][0]);
        printf("\n");
    }

    stack[top] = '$';
    printf("\nEnter the input string (end with $): ");
    scanf("%s", ip);

    i = 0;
    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    printf("%s\t\t%s\t\t", stack, ip);

    while (1) {
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k]) row = k;
            if (ip[i] == ter[k]) col = k;
        }

        if (stack[top] == '$' && ip[i] == '$') {
            printf("Accept\n");
            break;
        } else if (opt[row][col][0] == '<' || opt[row][col][0] == '=') {
            stack[++top] = ip[i];
            printf("Shift %c\n", ip[i]);
            i++;
        } else if (opt[row][col][0] == '>') {
            while (stack[top] != '<' && top > 0) top--;
            if (top > 0) top--;
            printf("Reduce\n");
        } else {
            printf("Reject\n");
            break;
        }
        printf("%s\t\t%s\t\t", stack, &ip[i]);
    }

    return 0;
}