/*Scrieti o functie care calculeazã lungimea celui mai lung
subsir de numere crescãtoare consecutive dintr-un sir de numere
întregi, folosind o stivã.
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

int secventaLunga(int vec[], int dim)
{
    if(dim == 0) return 0;

    Node *stack = NULL;
    int lungMax = 1;

    push(&stack, vec[0]);

    for(int i=1; i<dim; i++)
    {
        if(vec[i] >= stack->val){
            push(&stack, vec[i]);
        }

        else {int lung = 1;
              while(!isEmpty(stack))
              {
                  pop(&stack);
                    lung++;
              }

              if(lung > lungMax)
                    lungMax = lung;

              push(&stack, vec[i]);
        }
    }

    int lung = 0;
    //verific ultimul subsir
    while(!isEmpty(stack))
    {
     pop(&stack);
     lung++;
    }

    if(lung > lungMax) lungMax = lung;

    return lungMax;

}

int main()
{
    int vec[] = {3, 4, 1, 2, 3, -1, 1, 2, 3};
    int dim = sizeof(vec) / sizeof(vec[0]);
    printf("Lungimea celui mai lung subsir de numere crescãtoare consecutive: %d\n", secventaLunga(vec, dim));
    return 0;
}
