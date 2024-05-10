#include<limits.h>
#include "liste.h"

//header pentru stive
typedef struct stackNode{
    Team *subject;
    struct stackNode *next;
}StackNode;


Team *top(StackNode *top);

int isStackEmpty(StackNode *top);

void deleteStack(StackNode **top);

Team *pop(StackNode **top);

void push(StackNode **top, Team *v); 

void winnersAndLosersStacks(StackNode **winners, StackNode **losers, Queue *matches);

void writeTheMatchFormated(Match *match, char *fileOUT);

void writeWinnersTitleFormated(int numberOfRounds, char *fileOUT);

void writeWinnersFormated(StackNode *winners, char *fileOUT);



