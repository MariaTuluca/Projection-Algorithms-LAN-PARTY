/*Concatenati douã stive implementate cu listã.
Care este complexitatea solutiei?
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

void concatenateStacks(Node **stack1, Node *stack2) {
    if (*stack1 == NULL) { // dacã prima stivã este goalã, doar actualizãm varful stivei
        *stack1 = stack2;
    } else {
        Node *temp = *stack1;
        while (temp->next != NULL) { // parcurg prima stivã pânã la ultimul element
            temp = temp->next;
        }
        temp->next = stack2; // leg ultimul element al primei stive cu primul element al celei de-a doua stive
    }
}

int main()
{
    Node* stack1 = NULL;
    Node* stack2 = NULL;

    for (int i=0;i<3; i++)
        push (&stack1 ,i);

    for (int i=3;i<7; i++)
        push (&stack2 ,i);

    concatenateStacks(&stack1, stack2);

    afisareStack(stack1);

}
