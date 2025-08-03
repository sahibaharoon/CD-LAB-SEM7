#include <stdio.h>
#include <string.h>

#define MAX 50

int transition[MAX][MAX], n_states, n_symbols;
int final_states[MAX], n_final;
int distinguishable[MAX][MAX];
int group[MAX];
char symbols[MAX];  // input symbol list

int isFinal(int state) {
    for (int i = 0; i < n_final; i++)
        if (final_states[i] == state)
            return 1;
    return 0;
}

int symbolIndex(char sym) {
    for (int i = 0; i < n_symbols; i++) {
        if (symbols[i] == sym) return i;
    }
    return -1;
}

void inputDFA() {
    printf("Enter number of states: ");
    scanf("%d", &n_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &n_symbols);

    printf("Enter the input symbols (e.g., 0 1 or a b): ");
    for (int i = 0; i < n_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Initialize all transitions to -1
    for (int i = 0; i < n_states; i++)
        for (int j = 0; j < n_symbols; j++)
            transition[i][j] = -1;

    int n_transitions;
    printf("Enter number of transitions: ");
    scanf("%d", &n_transitions);

    printf("Enter each transition in the form: from_state input_symbol to_state\n");
    for (int i = 0; i < n_transitions; i++) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        int sym_idx = symbolIndex(sym);
        if (sym_idx != -1)
            transition[from][sym_idx] = to;
        else
            printf("Invalid symbol '%c'. Skipping.\n", sym);
    }

    printf("Enter number of final states: ");
    scanf("%d", &n_final);
    printf("Enter final states:\n");
    for (int i = 0; i < n_final; i++) {
        scanf("%d", &final_states[i]);
    }
}

void minimizeDFA() {
    memset(distinguishable, 0, sizeof(distinguishable));

    // Step 1: Final vs non-final
    for (int i = 0; i < n_states; i++) {
        for (int j = 0; j < i; j++) {
            if (isFinal(i) != isFinal(j)) {
                distinguishable[i][j] = 1;
            }
        }
    }

    // Step 2: Mark pairs by transitions
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n_states; i++) {
            for (int j = 0; j < i; j++) {
                if (distinguishable[i][j]) continue;
                for (int k = 0; k < n_symbols; k++) {
                    int a = transition[i][k];
                    int b = transition[j][k];
                    if (a == -1 || b == -1) continue;
                    if (a == b) continue;
                    int x = a > b ? a : b;
                    int y = a < b ? a : b;
                    if (distinguishable[x][y]) {
                        distinguishable[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    } while (changed);

    // Step 3: Group equivalent states
    for (int i = 0; i < n_states; i++)
        group[i] = i;

    for (int i = 0; i < n_states; i++) {
        for (int j = 0; j < i; j++) {
            if (!distinguishable[i][j]) {
                group[i] = group[j];  // assign to same group
            }
        }
    }

        // Step 4: Print minimized DFA as a table
        printf("Minimised transition table /n");
    printf("\n%-10s |", "State");
    for (int k = 0; k < n_symbols; k++) {
        printf(" on '%c'   |", symbols[k]);
    }
    printf(" Final\n");
    printf("-----------");
    for (int k = 0; k < n_symbols; k++) printf("+-----------");
    printf("+--------\n");

    int printed[MAX] = {0};

    for (int i = 0; i < n_states; i++) {
        if (group[i] != i || printed[group[i]]) continue;
        printed[group[i]] = 1;

        // Print merged state name
        printf("[");
        for (int j = 0; j < n_states; j++) {
            if (group[j] == group[i]) printf("%d,", j);
        }
        printf("\b]     |");

        // Print transitions
        for (int k = 0; k < n_symbols; k++) {
            int target = transition[i][k];
            if (target == -1) {
                printf("    -     |");
                continue;
            }

            int target_group = group[target];
            printf(" [");
            for (int j = 0; j < n_states; j++) {
                if (group[j] == target_group) printf("%d,", j);
            }
            printf("\b]    |");
        }

        // Print if final
        printf("  %s\n", isFinal(i) ? "Yes" : "No");
    }
}

int main() {
    inputDFA();
    minimizeDFA();
    return 0;
}