
 
#include<limits.h>
#include<stdlib.h>
#include "liste.h"

#ifndef COZI_H
#define COZI_H
// două structuri pentru definirea cozilor
typedef struct queueNode{
    Match *subject;
    struct queueNode *next;
}QueueNode;

typedef struct Queue{
    QueueNode *front, *rear;
}Queue;

#endif

int isQueueEmpty(Queue *q);

Queue* createQueue();

void enQueue(Queue *q, Match *v);

Match *deQueue(Queue *q);

void deleteQueue(Queue *q);





