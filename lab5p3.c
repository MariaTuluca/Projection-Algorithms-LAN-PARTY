/*Implementati o coadă folosind două stive.*/

#include<stdio.h>
#include<stdlib.h>

typedef int Data;

typedef struct Node{
    Data val;
    struct Node* next;
} Node;

typedef struct {
    Node *top;
} Stack;

typedef struct{
Stack *s1, *s2;
}Queue;

int isEmpty(Stack *s){
    return s->top == NULL;
}

void push(Stack *s , Data v)
{
    Node* newNode =(Node*)malloc(sizeof(Node));
    newNode->val=v;
    newNode->next = s->top;
    s->top=newNode;
}

Data pop(Stack *s)
{
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return NULL;
    }

    Node *temp = s->top;
    Data val = temp->val;
    s->top = s->top->next;
    free(temp);
    return val;
}

// Funcție pentru a crea o coadă nouă
Queue* createQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->s1 = (Stack*)malloc(sizeof(Stack));
    q->s1->top = NULL;
    q->s2 = (Stack*)malloc(sizeof(Stack));
    q->s2->top = NULL;
    return q;
}

void enQueue(Queue *q, Data v)
{
    while (!isEmpty(q->s1)) {
        push(q->s2, pop(q->s1));
    }

    push(q->s1, v);

    while (!isEmpty(q->s2)) {
        push(q->s1, pop(q->s2));
    }
}

Data deQueue(Queue *q)
{
    if (isEmpty(q->s1)) {
        printf("Queue is empty\n");
        return NULL;
    }

    return pop(q->s1);
}

int main() {
    Queue *q = createQueue();

    enQueue(q, 1);
    enQueue(q, 2);
    enQueue(q, 3);

    printf("Elementul eliminat din coada: %d\n", deQueue(q));
    printf("Elementul eliminat din coada: %d\n", deQueue(q));
    printf("Elementul eliminat din coada: %d\n", deQueue(q));
    printf("Elementul eliminat din coada: %d\n", deQueue(q)); // Coada este acum goală

    return 0;
}
