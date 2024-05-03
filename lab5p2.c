/*Implementati o stivă folosind două cozi.*/

#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

typedef int Data;

typedef struct{
    Data val;
    struct Node* next;
}Node;

// Definirea unei cozi
typedef struct {
    Node *front, *rear;
} Queue;

// Definirea unei stive care utilizează două cozi
typedef struct {
    Queue *q1, *q2;
} Stack;

// Funcție pentru a crea o coadă nouă
Queue* createQueue()
{
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Funcție pentru a crea o stivă nouă
Stack* createStack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->q1 = createQueue();
    stack->q2 = createQueue();
    return stack;
}

// Funcție pentru a verifica dacă o coadă este goală
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// Funcție pentru a adăuga un element la coadă
void enQueue ( Queue *q, Data v)
{
    Node * newNode =( Node *) malloc ( sizeof ( Node ));
    newNode->val=v;
    newNode->next = NULL ;
    if (q->rear == NULL ) q->rear = newNode ;
    else {(q->rear)->next = newNode ;
          (q->rear)= newNode ;
         }
    if (q->front == NULL ) q->front =q->rear ;
}

// Funcție pentru a elimina și returna un element din coadă
Data deQueue(Queue *q)
{
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return INT_MIN;
        }

    Node *temp = q->front;
    Data val = temp->val;
    q->front = q->front->next;
    free(temp);
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return val;
}

// Funcție pentru a adăuga un element la stivă
void push(Stack *stack, Data val) {
    enQueue(stack->q1, val);
}

// Funcție pentru a elimina și returna un element din stivă
Data pop(Stack *stack) {
    if (isEmpty(stack->q1) && isEmpty(stack->q2)) {
        printf("Stack is empty\n");
        return INT_MIN;
    }

    // Se mută toate elementele din q1 în q2, exceptând ultimul element
    while (!isEmpty(stack->q1)) {
        enQueue(stack->q2, deQueue(stack->q1));
    }

    // Se elimină și se returnează ultimul element din q2
    Data val = deQueue(stack->q2);

    Queue *temp = stack->q1;
    stack->q1 = stack->q2;
    stack->q2 = temp;

    return val;
}

int main() {
    Stack *stack = createStack();

    push(stack, 1);
    push(stack, 2);
    push(stack, 3);

    printf("Elementul eliminat din stiva: %d\n", pop(stack));
    printf("Elementul eliminat din stiva: %d\n", pop(stack));
    printf("Elementul eliminat din stiva: %d\n", pop(stack));
    printf("Elementul eliminat din stiva: %d\n", pop(stack)); // Stiva este acum goală

    return 0;
}
