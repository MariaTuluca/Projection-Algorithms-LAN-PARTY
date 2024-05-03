
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int Data;

typedef struct Elem{
    Data val;
    struct Elem* next;
} Node;

void printNode(Node * head)
{
    while(head != NULL)
    {
        printf("%d ",head->val);
        head = head->next;
    }
}

void addAtBeginning(Node **head, int v){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->val = v;
	newNode->next = *head;
	*head = newNode;
}

void addAtEnd(Node** head, int v){
	Node *aux = *head;
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->val = v;
	if (*head == NULL) addAtBeginning(head, v);
	else{
		while (aux->next!=NULL)
			aux = aux->next;
		aux->next = newNode;
		newNode->next = NULL;
	}
}

void deleteNode(Node **head, int v){
	if (*head==NULL) return;
	Node *headcopy = *head;
	if (headcopy->val==v){
		*head = (*head)->next;
		free(headcopy);
		return;
	}
	Node *prev = *head;
	while (headcopy!=NULL){
		if(headcopy->val!=v){
			prev = headcopy;
			headcopy = headcopy->next;
		}else{
			prev->next = headcopy->next;
			free(headcopy);
			return;
		}
	}
}

Node* searchElement(Node *head, Data valoare)
{
    Node* gasit = head;

    while(gasit != NULL)
    {
        if(gasit->val == valoare) return gasit; //returneaza primul element gasit

        gasit = gasit->next;
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    Node *Bile = NULL;
    Data i = 1;  //contor pentru valoarea culorii

    for( int j = 0; j<15; ++j)
    {
        addAtEnd(&Bile, i);
    }

    for( int j = 0; j<6; ++j)
    {
        i++;
        addAtEnd(&Bile, i);
    }

    printNode(Bile);

    Node *Meci = NULL;

    while(Bile!=NULL && Bile->val == 1)
    {
        deleteNode(&Bile, Bile->val);
        addAtEnd(&Meci, 1);
    }

    if(Bile != NULL)
    {
        Data val_culoare = Bile->val;
        Node *culoareGasita = searchElement(Bile, val_culoare);

    if ( culoareGasita!= NULL) {
        addAtEnd(&Meci, culoareGasita->val);
        deleteNode(&Bile, val_culoare);
    }

    }

    printf("\n Bile:\n");
   printNode(Bile);
    printf("\n Meci:");
   printNode(Meci);

    while (Bile != NULL)
    { //memoria
        Node* temp = Bile;
        Bile = Bile->next;
        free(temp);
    }

    while (Meci != NULL)
    {
        Node* temp = Meci;
        Meci = Meci->next;
        free(temp);
    }



}
