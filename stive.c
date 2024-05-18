#include "stive.h"

//fișier cu funcții pentru stive, create, dar și prelucrate din curs

Team *top(StackNode *top)
{
	return top->subject;
}

int isStackEmpty(StackNode *top)
{
	return top==NULL;
}

void deleteStack(StackNode **top)
{
	StackNode *temp;
	while ((*top)!=NULL){ 
		temp = *top;
		*top = (*top)->next;
		free(temp);
	}
}

Team *pop(StackNode **top) 
{
    StackNode *temp = (*top);
	Team *aux = temp->subject;

	*top=(*top)->next;
	free(temp);
	return aux;
}

void push(StackNode **top, Team *v) 
{
	StackNode* newNode = malloc(sizeof(StackNode));
	if(newNode == NULL)
	{
		printf("Eroare alocare memorie pentru newNode stack.\n");
		return;
	}

	newNode->subject = v;
	newNode->next = *top;
	*top = newNode;
}
