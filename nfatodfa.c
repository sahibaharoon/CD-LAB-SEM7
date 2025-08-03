#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 26
#define MAX_DFA_STATES 10000

int dfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES] = {0};
int go[MAX_DFA_STATES][MAX_SYMBOLS] = {0};
int visited[MAX_DFA_STATES] = {0};
int queue[MAX_DFA_STATES], front = 0, rear = 0;
char symbols[MAX_SYMBOLS];
int symbolCount;

int getSymbolIndex(char ch) {
    for (int i = 0; i < symbolCount; i++) {
        if (symbols[i] == ch) return i;
    }
    return -1;
}

void enqueue(int state) {
    if (!visited[state]) {
        queue[rear++] = state;
        visited[state] = 1;
    }
}

int main() {
    int st, rel, in;

    printf("Enter number of NFA states: ");
    scanf("%d", &st);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbolCount);

    printf("Enter %d unique input symbols (e.g., a b): ", symbolCount);
    for (int i = 0; i < symbolCount; i++) {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter number of transitions: ");
    scanf("%d", &rel);

    printf("Enter transitions in format: <from_state> <symbol> <to_state>.  eg: 0 a 1\n");
    for (int i = 0; i < rel; i++) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        int idx = getSymbolIndex(sym);
        if (idx == -1) {
            printf("Invalid symbol '%c'\n", sym);
            return 1;
        }
        dfa[from][idx][to] = 1;
    }

    printf("Enter initial state: ");
    scanf("%d", &in);

    int start = (1 << in);
    enqueue(start);

    // Build DFA using subset construction
    while (front < rear) {
        int current = queue[front++];

        for (int sym = 0; sym < symbolCount; sym++) {
            int next = 0;
            for (int i = 0; i < st; i++) {
                if (current & (1 << i)) {
                    for (int j = 0; j < st; j++) {
                        if (dfa[i][sym][j]) {
                            next |= (1 << j);
                        }
                    }
                }
            }
            go[current][sym] = next;
            if (next && !visited[next]) {
                enqueue(next);
            }
        }
    }

    // Print DFA Transition Table
    printf("\n DFA Transition Table:\n");
    printf("State\t\t");
    for (int i = 0; i < symbolCount; i++) {
        printf("%c\t", symbols[i]);
    }
    printf("\n");

    for (int i = 0; i < rear; i++) {
        int current = queue[i];

        // Print current state
        printf("{");
        for (int j = 0; j < st; j++) {
            if (current & (1 << j)) {
                printf("q%d,", j);
            }
        }
        printf("}\t");

        // Print transitions
        for (int sym = 0; sym < symbolCount; sym++) {
            int target = go[current][sym];
            if (!target) {
                printf("{}\t");
            } else {
                printf("{");
                for (int j = 0; j < st; j++) {
                    if (target & (1 << j)) {
                        printf("q%d,", j);
                    }
                }
                printf("}\t");
            }
        }
        printf("\n");
    }

    return 0;
}