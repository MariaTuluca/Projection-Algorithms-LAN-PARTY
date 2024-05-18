#include "cozi.h"

// fișier cu funcții legate de cozi, luate din cursuri, dar și create de mine

int isQueueEmpty(Queue *q)
{
    return (q->front == NULL);
}

Queue* createQueue()
{
    Queue *q;
    q=(Queue*)malloc(sizeof(Queue));
    if(q == NULL) return NULL;
    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue *q, Match *v)
{
    QueueNode *newNode =(QueueNode*)malloc(sizeof(QueueNode));
    newNode->subject = v;
    newNode->next = NULL;
    if(q->rear == NULL) q->rear = newNode;
    else{ 
    (q->rear)->next = newNode;
    (q->rear) = newNode;
    }
    if(q->front == NULL) q->front = q->rear;
}

Match *deQueue(Queue *q)
{
    QueueNode *aux = q->front; 
    Match *d = aux->subject;

    if(q->front == q->rear)
        q->front = q->rear = NULL;
    else q->front = q->front->next;

    if(q->front == NULL)
        return NULL;

    free(aux);
    return d;

}

void deleteQueue(Queue *q)
{
    QueueNode *aux;
    while(!isQueueEmpty(q))
    {
        aux = q->front;
        q->front = q->front->next;
        free(aux);
    }
    free(q);
    q = NULL;
}

