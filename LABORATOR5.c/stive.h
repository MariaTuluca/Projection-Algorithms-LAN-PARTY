#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct valori{
    int m;
    int n;
}Valori;

typedef struct N{
    Valori val;
    struct Node *next;
}Node;

int isEmpty(Node*top);

void deleteStack(Node**top);

Valori pop(Node**top);

void push(Node**top, int v1, int v2);

Valori top(Node *top);

void printStack(Node* stack);

