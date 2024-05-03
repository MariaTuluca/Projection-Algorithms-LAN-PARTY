/*Implementati o coadă folosind o listă dublu înlănutuită
circulară cu santinelă.*/

#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct Node {
    Data val;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *sentinel;
} Queue;

Queue* createQueue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->sentinel = (Node*)malloc(sizeof(Node));
    q->sentinel->prev = q->sentinel;
    q->sentinel->next = q->sentinel;
    return q;
}

int isEmpty(Queue *q) {
    return q->sentinel->next == q->sentinel;
}

void enQueue(Queue *q, Data val) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;

    newNode->prev = q->sentinel->prev;
    newNode->next = q->sentinel;
    q->sentinel->prev->next = newNode;
    q->sentinel->prev = newNode;
}

// Funcție pentru a elimina și returna primul element din coadă
Data deQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return INT_MIN;
    }

    // Se obține valoarea primului nod
    Node *temp = q->sentinel->next;
    Data val = temp->val;

        // Se elimină primul nod
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);

    return val;
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
