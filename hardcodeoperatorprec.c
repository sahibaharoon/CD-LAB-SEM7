#include <stdio.h>
#include <string.h>

char input[20], stack[20];
int top = -1, i = 0;

// Operator precedence table
//        i    +    *    $
char prec[4][4] = {
    {'R', '>', '>', '>'},  // i
    {'<', '>', '<', '>'},  // +
    {'<', '>', '>', '>'},  // *
    {'<', '<', '<', 'A'}   // $
};

char symb[4] = {'i', '+', '*', '$'};

int main() {
    printf("Enter the input: ");
    scanf("%s", input);

    stack[++top] = '$';

    printf("\nStack\t\tInput\t\tAction\n");

    while (1) {
        // Print stack
        for (int j = 0; j <= top; j++)
            printf("%c", stack[j]);
        printf("\t\t%s\t\t", &input[i]);

        int row = -1, col = -1;

        // Find column (current input symbol)
        for (int k = 0; k < 4; k++) {
            if (input[i] == symb[k]) {
                col = k;
                break;
            }
        }

        // Find row (top-most terminal in stack)
        int pos = top;
        while (stack[pos] == 'E' && pos >= 0)
            pos--;
        for (int k = 0; k < 4; k++) {
            if (stack[pos] == symb[k]) {
                row = k;
                break;
            }
        }

        if (row == -1 || col == -1) {
            printf("Rejected (Invalid symbol)\n");
            break;
        }

        char action = prec[row][col];

        if (action == '<') {
            stack[++top] = input[i++];
            printf("Shift\n");
        } 
        else if (action == '>') {
            // Perform reductions
            if (stack[top] == 'i') {
                stack[top] = 'E';
                printf("Reduce E -> i\n");
            } 
            else if (stack[top] == 'E' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
                top -= 2;
                printf("Reduce E -> E+E\n");
            } 
            else if (stack[top] == 'E' && stack[top - 1] == '*' && stack[top - 2] == 'E') {
                top -= 2;
                printf("Reduce E -> E*E\n");
            } 
            else {
                printf("Rejected (Invalid reduction)\n");
                break;
            }
        } 
        else if (action == 'A') {
            if (stack[top] == 'E' && stack[top - 1] == '$' && input[i] == '$') {
                printf("Accept\n");
                break;
            } else {
                printf("Rejected\n");
                break;
            }
        } 
        else {
            printf("Rejected\n");
            break;
        }
    }

    return 0;
}
