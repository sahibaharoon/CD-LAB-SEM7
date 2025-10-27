#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

int n;
char prod[MAX][10];
char firstSet[MAX], followSet[MAX];

// ---------- Helper Functions ----------
void addToSet(char *set, char c) {
    if (strchr(set, c) == NULL) {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void FIRST(char c, char *result);
void FOLLOW(char c, char *result);

// ---------- FIRST Calculation ----------
void FIRST(char c, char *result) {
    if (!isupper(c)) {  // terminal or epsilon
        addToSet(result, c);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            int j = 2;
            while (prod[i][j] != '\0') {
                char next = prod[i][j];
                char temp[10] = "";
                FIRST(next, temp);

                int hasEpsilon = 0;
                for (int k = 0; k < strlen(temp); k++) {
                    if (temp[k] == 'e')
                        hasEpsilon = 1;
                    else
                        addToSet(result, temp[k]);
                }

                if (!hasEpsilon) break;  // stop if epsilon not found
                j++;
                if (prod[i][j] == '\0') addToSet(result, 'e');  // all can produce epsilon
            }
        }
    }
}

// ---------- FOLLOW Calculation ----------
void FOLLOW(char c, char *result) {
    if (prod[0][0] == c)
        addToSet(result, '$');  // start symbol gets $

    for (int i = 0; i < n; i++) {
        char *rhs = strchr(prod[i], '=') + 1;
        for (int j = 0; rhs[j] != '\0'; j++) {
            if (rhs[j] == c) {
                // Case 1: if not the last symbol
                int k = j + 1;
                while (rhs[k] != '\0') {
                    char next = rhs[k];
                    char temp[10] = "";
                    FIRST(next, temp);
                    int hasEpsilon = 0;

                    for (int x = 0; x < strlen(temp); x++) {
                        if (temp[x] == 'e')
                            hasEpsilon = 1;
                        else
                            addToSet(result, temp[x]);
                    }

                    if (!hasEpsilon) break;  // stop if epsilon not in FIRST
                    k++;
                }

                // Case 2: if at end or everything after can produce epsilon
                if (rhs[k] == '\0' && prod[i][0] != c) {
                    char tempFollow[10] = "";
                    FOLLOW(prod[i][0], tempFollow);
                    for (int x = 0; x < strlen(tempFollow); x++)
                        addToSet(result, tempFollow[x]);
                }
            }
        }
    }
}

// ---------- MAIN ----------
int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (use e for epsilon, e.g. A=a or A=e):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    char done[MAX] = "";
    for (int i = 0; i < n; i++) {
        char nt = prod[i][0];
        if (strchr(done, nt)) continue;
        strncat(done, &nt, 1);

        firstSet[0] = '\0';
        FIRST(nt, firstSet);
        printf("FIRST(%c) = { ", nt);
        for (int j = 0; j < strlen(firstSet); j++)
            printf("%c ", firstSet[j]);
        printf("}\n");

        followSet[0] = '\0';
        FOLLOW(nt, followSet);
        printf("FOLLOW(%c) = { ", nt);
        for (int j = 0; j < strlen(followSet); j++)
            printf("%c ", followSet[j]);
        printf("}\n\n");
    }
    return 0;
}
