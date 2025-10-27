#include <stdio.h>

// Define the number of states in the NFA
#define NUM_STATES 3

/**
 * @brief Recursively finds the epsilon closure of a given state using DFS.
 * @param state The current state we are visiting.
 * @param closure_set An array (acting as a set) to store the result.
 * @param epsilon_transitions The NFA's transition table (adjacency matrix).
 */
void find_epsilon_closure(int state, int closure_set[NUM_STATES], int transitions[NUM_STATES][NUM_STATES]) {
    // Add the current state to its own closure
    closure_set[state] = 1;

    // Explore all epsilon transitions
    for (int i = 0; i < NUM_STATES; i++) {
        if (transitions[state][i] == 1 && closure_set[i] == 0) {
            find_epsilon_closure(i, closure_set, transitions);
        }
    }
}

int main() {
    int epsilon_transitions[NUM_STATES][NUM_STATES];

    printf("Enter the epsilon transitions for %d states (1 for yes, 0 for no):\n", NUM_STATES);

    // Input the transition table
    for (int i = 0; i < NUM_STATES; i++) {
        for (int j = 0; j < NUM_STATES; j++) {
            printf("  Transition from state %d to state %d: ", i, j);
            scanf("%d", &epsilon_transitions[i][j]);
        }
    }

    // Print the entered table
    printf("\n--- Transition Table ---\n");
    for (int i = 0; i < NUM_STATES; i++) {
        printf("  ");
        for (int j = 0; j < NUM_STATES; j++) {
            printf("%d ", epsilon_transitions[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------\n\n");

    // Compute epsilon closure for each state
    for (int start_state = 0; start_state < NUM_STATES; start_state++) {
        int closure_set[NUM_STATES] = {0};

        // Find closure for current state
        find_epsilon_closure(start_state, closure_set, epsilon_transitions);

        // Print result
        printf("Epsilon closure of state %d: { ", start_state);
        for (int i = 0; i < NUM_STATES; i++) {
            if (closure_set[i] == 1)
                printf("%d ", i);
        }
        printf("}\n");
    }

    return 0;
}
