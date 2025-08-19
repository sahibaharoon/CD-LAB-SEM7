#include <stdio.h>
#include <string.h>

#define MAX 100

int tempCount = 1;

// Generate a new temp variable like t1, t2, ...
void newTemp(char *t) {
    sprintf(t, "t%d", tempCount++);
}

// Precedence function
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int main() {
    char expr[MAX];
    char temp[10];
    int i, j;

    printf("Enter expression: ");
    scanf("%s", expr);

    printf("\nIntermediate Code Generation:\n");

    // Work on a copy of expression tokens
    char tokens[50][10]; // split into symbols
    int n = 0;

    // Split expr into individual tokens (for now: single-char operands and operators)
    for (i = 0; expr[i] != '\0'; i++) {
        char buf[2] = {expr[i], '\0'};
        strcpy(tokens[n++], buf);
    }

    // Process operators by precedence
    for (int p = 2; p > 0; p--) {
        for (i = 0; i < n; i++) {
            if (precedence(tokens[i][0]) == p) {
                char left[10], right[10];
                strcpy(left, tokens[i - 1]);
                strcpy(right, tokens[i + 1]);

                newTemp(temp);
                printf("%s = %s %s %s\n", temp, left, tokens[i], right);

                // Replace (left op right) with temp
                strcpy(tokens[i - 1], temp);

                // Shift remaining tokens left
                for (j = i + 2; j < n; j++) {
                    strcpy(tokens[j - 2], tokens[j]);
                }
                n -= 2;

                // Restart from beginning for this precedence
                i = -1;
            }
        }
    }

    return 0;
}
