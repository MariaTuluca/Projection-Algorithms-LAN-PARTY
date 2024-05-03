#include"stive.h"


int isEmpty(Node*top){
	return top==NULL;
}

void deleteStack(Node**top){
	Node  *temp;
	while ((*top)!=NULL){ // !isEmpty(*top)
		temp=*top;
		*top=(*top)->next;
		free(temp);
	}
}

Valori pop(Node**top) {
    Valori aux;
	if (isEmpty(*top)) return aux;

	Node *temp=(*top);
	aux.m = temp->val.m;   //modif
	aux.n = temp->val.n;
	*top=(*top)->next;
	free(temp);
	return aux;
}

void push(Node**top, int v1, int v2) {
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->val.m = v1;    //modif
	newNode->val.n = v2;
	newNode->next=*top;
	*top=newNode;
}

Valori top(Node *top){
	if (isEmpty(top)) return INT_MIN;
	return top->val;
}

void printStack(Node* stack){
    Valori aux;
    aux = pop(&stack);  //modif
	while (!isEmpty(stack))
		printf("%d %d", aux.m, aux.n);
}



