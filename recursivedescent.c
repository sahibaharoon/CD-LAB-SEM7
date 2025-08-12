#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i = 0, error = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void printStep(const char *rule) {
    printf("Step: %-15s | Remaining input: %s\n", rule, &input[i]);
}

void E() {
    printStep("E -> T E'");
    T();
    Eprime();
}

void Eprime() {
    if (input[i] == '+') {
        printStep("E' -> + T E'");
        i++;
        T();
        Eprime();
    } else {
        printStep("E' -> ε");
    }
}

void T() {
    printStep("T -> F T'");
    F();
    Tprime();
}

void Tprime() {
    if (input[i] == '*') {
        printStep("T' -> * F T'");
        i++;
        F();
        Tprime();
    } else {
        printStep("T' -> ε");
    }
}

void F() {
    if (input[i] == '(') {
        printStep("F -> ( E )");
        i++;
        E();
        if (input[i] == ')')
            i++;
        else
            error = 1;
    }
    else if (isalpha(input[i])) {
        printStep("F -> id");
        i++;
        while (isalnum(input[i]) || input[i] == '_')
            i++;
    }
    else {
        error = 1;
    }
}

int main() {
    printf("Enter an arithmetic expression:\n");
    scanf("%s", input);

    E();

    if (strlen(input) == i && error == 0)
        printf("\nAccepted..!!!\n");
    else
        printf("\nRejected..!!!\n");

    return 0;
}
