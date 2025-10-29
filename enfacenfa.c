#include <stdio.h>
#include <string.h>

#define MAX 20

char states[MAX][5], symbols[MAX][5];
int nStates, nSymbols;
int trans[MAX][MAX][MAX];   // trans[state][symbol][target] = 1 if transition exists
int epsTrans[MAX][MAX];     // epsilon transitions

int findIndex(char arr[MAX][5], int n, char *str) {
    for (int i = 0; i < n; i++)
        if (strcmp(arr[i], str) == 0)
            return i;
    return -1;
}

// Find epsilon closure of a state (DFS)
void epsilonClosure(int s, int visited[]) {
    visited[s] = 1;
    for (int i = 0; i < nStates; i++)
        if (epsTrans[s][i] && !visited[i])
            epsilonClosure(i, visited);
}

int main() {
    int nTrans;
    printf("Enter number of states: ");
    scanf("%d", &nStates);
    printf("Enter state names (e.g. q0 q1 q2 ...): ");
    for (int i = 0; i < nStates; i++)
        scanf("%s", states[i]);

    printf("Enter number of input symbols (excluding ε): ");
    scanf("%d", &nSymbols);
    printf("Enter symbols (e.g. a b): ");
    for (int i = 0; i < nSymbols; i++)
        scanf("%s", symbols[i]);

    // Initialize transitions
    memset(trans, 0, sizeof(trans));
    memset(epsTrans, 0, sizeof(epsTrans));

    printf("Enter number of transitions: ");
    scanf("%d", &nTrans);
    printf("Enter transitions (e.g. q0 a q1 or q0 e q2):\n");

    for (int i = 0; i < nTrans; i++) {
        char from[5], sym[5], to[5];
        scanf("%s %s %s", from, sym, to);
        int s1 = findIndex(states, nStates, from);
        int s2 = findIndex(states, nStates, to);

        if (strcmp(sym, "e") == 0 || strcmp(sym, "ε") == 0)
            epsTrans[s1][s2] = 1;
        else {
            int symIndex = findIndex(symbols, nSymbols, sym);
            trans[s1][symIndex][s2] = 1;
        }
    }
    
    printf("\nEpsilon-closures:\n");
for (int i = 0; i < nStates; i++) {
    int visited[MAX] = {0};
    epsilonClosure(i, visited);
    printf("ε-closure(%s) = { ", states[i]);
    for (int j = 0; j < nStates; j++)
        if (visited[j])
            printf("%s ", states[j]);
    printf("}\n");
}

    printf("\n--- NFA WITHOUT ε TRANSITIONS ---\n");
    for (int i = 0; i < nStates; i++) {
        int eclose[MAX] = {0};
        epsilonClosure(i, eclose);  // ε-closure of i

        for (int a = 0; a < nSymbols; a++) {
            int newReach[MAX] = {0};

            // For each state in ε-closure(i)
            for (int j = 0; j < nStates; j++) {
                if (eclose[j]) {
                    // For each transition on symbol a
                    for (int k = 0; k < nStates; k++) {
                        if (trans[j][a][k]) {
                            int temp[MAX] = {0};
                            epsilonClosure(k, temp);
                            // Add all states from ε-closure(k)
                            for (int x = 0; x < nStates; x++)
                                if (temp[x]) newReach[x] = 1;
                        }
                    }
                }
            }

            // Print resulting transitions
            for (int t = 0; t < nStates; t++) {
                if (newReach[t])
                    printf("%s %s %s\n", states[i], symbols[a], states[t]);
            }
        }
    }

    return 0;
}
