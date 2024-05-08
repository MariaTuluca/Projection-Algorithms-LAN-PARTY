#include<limits.h>
#include<stdlib.h>
#include "liste.h"
#include "stive.h"

// două structuri pentru definirea cozii 
typedef struct queueNode{
    Match *subject;
    struct queueNode *next;
}QueueNode;

typedef struct Queue{
    QueueNode *front, *rear;
}Queue;

int isQueueEmpty(Queue *q);

Queue* createQueue();

void enQueue(Queue *q, Match *v);

Match *deQueue(Queue *q);

void deleteQueue(Queue *q);

void populateQueue(Queue **matches, ListOfTeams *teamList);

void remakeQueueOfMatches(Queue *matches, StackNode **winners, int *numberOfTeams);




