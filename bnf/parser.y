%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// AST Node Structure
typedef struct ASTNode {
    char* type;
    struct ASTNode *left;
    struct ASTNode *right;
    int value; // For numbers
} ASTNode;

ASTNode* createNode(char* type, ASTNode* left, ASTNode* right, int value);
void printAST(ASTNode* node, int indent);

ASTNode* root; // Global AST root

int yyerror(const char* s);
int yylex(void);
%}

%union {
    int num;
    struct ASTNode* ast;
}

%token <num> NUMBER
%left '+' '-'
%left '*' '/'

%type <ast> expr term factor
%start input   // Set start symbol
%%

input:
      /* empty */
    | input expr '\n' { root = $2; printAST(root, 0); }
    ;

expr
    : expr '+' term    { $$ = createNode("+", $1, $3, 0); }
    | expr '-' term    { $$ = createNode("-", $1, $3, 0); }
    | term             { $$ = $1; }
    ;

term
    : term '*' factor  { $$ = createNode("*", $1, $3, 0); }
    | term '/' factor  { $$ = createNode("/", $1, $3, 0); }
    | factor           { $$ = $1; }
    ;

factor
    : '(' expr ')'     { $$ = $2; }
    | NUMBER           { $$ = createNode("num", NULL, NULL, $1); }
    ;


%%

ASTNode* createNode(char* type, ASTNode* left, ASTNode* right, int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = strdup(type); // safe string copy
    node->left = left;
    node->right = right;
    node->value = value;
    return node;
}

void printAST(ASTNode* node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");
    if (strcmp(node->type, "num") == 0)
        printf("%s: %d\n", node->type, node->value);
    else
        printf("%s\n", node->type);
    printAST(node->left, indent + 1);
    printAST(node->right, indent + 1);
}

int main() {
    printf("Enter expression:\n");
    if (yyparse() == 0) {
        printAST(root, 0);
    }
    return 0;
}

int yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

