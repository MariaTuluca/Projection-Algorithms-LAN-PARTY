#include<limits.h>
#include "liste.h"

//header pentru stive
#ifndef STIVE_H
#define STIVE_H
typedef struct stackNode{
    Team *subject;
    struct stackNode *next;
}StackNode;

#endif

Team *top(StackNode *top);

int isStackEmpty(StackNode *top);

void deleteStack(StackNode **top);

Team *pop(StackNode **top);

void push(StackNode **top, Team *v); 



