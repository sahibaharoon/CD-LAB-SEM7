#include <stdio.h>
#include <string.h>

#define MAX 20

char states[MAX][5];       // store state names
int n;                     // number of states
int epsTrans[MAX][MAX];    // epsilon transition matrix

int findIndex(char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(states[i], name) == 0)
            return i;
    }
    return -1;
}

void findEpsilonClosure(int state, int visited[]) {
    visited[state] = 1;
    for (int i = 0; i < n; i++) {
        if (epsTrans[state][i] && !visited[i])
            findEpsilonClosure(i, visited);
    }
}

int main() {
    int numTransitions;
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter state names (like q0 q1 q2 ...): ");
    for (int i = 0; i < n; i++)
        scanf("%s", states[i]);

    // initialize epsilon matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            epsTrans[i][j] = 0;

    printf("Enter number of transitions: ");
    scanf("%d", &numTransitions);

    printf("Enter transitions (e.g. q0 e q1 or q0 1 q2):\n");
    for (int i = 0; i < numTransitions; i++) {
        char from[5], symbol[5], to[5];
        scanf("%s %s %s", from, symbol, to);

        int s1 = findIndex(from);
        int s2 = findIndex(to);

        // Only store epsilon transitions
        if (strcmp(symbol, "e") == 0 || strcmp(symbol, "ε") == 0)
            epsTrans[s1][s2] = 1;
    }

    printf("\nEpsilon-Closures:\n");
    for (int i = 0; i < n; i++) {
        int visited[MAX] = {0};
        findEpsilonClosure(i, visited);
        printf("ε-closure(%s) = { ", states[i]);
        for (int j = 0; j < n; j++)
            if (visited[j])
                printf("%s ", states[j]);
        printf("}\n");
    }

    return 0;
}
