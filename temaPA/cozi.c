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
    q->front =q->rear = NULL;
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
    QueueNode *aux; 
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

//funcție pentru refacere coadă de meciuri
void remakeQueueOfMatches(Queue *matches, StackNode **winners, int *numberOfTeams)
{//inițializez numărul de teams din stivă cu 0
    *numberOfTeams = 0;

    while(!isStackEmpty(*winners))
    {//creez un nou match
        Match *new_match = malloc(sizeof(Match));
        if(new_match == NULL)
        {   printf("Eroare la alocare spațiu new_match!");
            return;
        }
        (*numberOfTeams)++;
        //prima și a doua echipă din stiva winners vor forma un nou match 
        Team *team1 = pop(winners);
        if((*winners)->next != NULL)
            {   (*numberOfTeams)++;
                Team *team2 = pop(winners);
                new_match->team_1 = team1;
                new_match->team_2 = team2;
            }
        //adaug meciul în coadă
        enQueue(matches, new_match);
    }
}