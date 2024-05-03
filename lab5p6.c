/*Inversati ordinea elementelor dintr-o stivã folosind doar
operatiile push si pop.
*/

#include<stdio.h>
#include<stdlib.h>

typedef int Data;

typedef struct{
    Data val;
    struct Node* next;
}Node;

int isEmpty(Node *top){
    return top == NULL ;
}

void afisareStack(Node *head)
{
    while(head != NULL)
    {
        printf("%d ",head->val);
        head = head->next;
    }

    printf("\n");
}

void push(Node **top , Data v)
{
    Node* newNode =(Node*)malloc(sizeof(Node));
    newNode->val=v;
    newNode->next = *top;
    *top=newNode;
}

Data pop( Node **top)
{
    if ( isEmpty(*top)) return INT_MIN ;
    Node *temp =(*top);
    Data aux=temp->val;
    *top =(*top)->next ;
    free(temp);
return aux;
}

void reverseStack(Node **stack)
{
    Node *tempStack = NULL;
    Node *current = *stack;

    while (current != NULL) {
        push(&tempStack, current->val);
        current = current->next;
    }

    // Eliberãm memoria pentru nodurile din stiva originalã
    while (*stack != NULL) {
        Node *temp = *stack;
        *stack = (*stack)->next;
        free(temp);
    }

    // Refacem stiva originalã din stiva temporarã
    *stack = tempStack;
}

int main()
{
    Node *stack = NULL;

    push(&stack, 2);
    push(&stack, 4);
    push(&stack, 6);
    push(&stack, 8);

    printf("Stiva originala: ");
    afisareStack(stack);

    reverseStack(&stack);

    printf("Stiva intoarsa: ");
    afisareStack(stack);
}
