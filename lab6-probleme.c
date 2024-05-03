#include"stive.h"
#include<stdio.h>
#include<stdlib.h>

int ack(int m, int n)
{
    Node* stack = NULL;

    Valori aux;
    aux.m = m;
    aux.n = n;

    push(&stack, m, n);

    int nou = 0;

while(!isEmpty(stack))
  {
    aux = pop(&stack);

    if (aux.m == 0)
    {
        nou = aux.n + 1;
        if(isEmpty(stack)) return nou;

        stack->val.n = nou;
    }

    else if ((aux.m > 0) && (aux.n == 0))
    {
        int mNou = m-1;
        push(&stack, mNou, 1);
    }

    else if ((aux.m > 0) && (aux.n > 0))
    {
        Valori elem;
        elem.m = aux.m - 1;
        elem.n = 0;

        push(&stack, elem.m, elem.n);

        elem.m = aux.m;
        elem.n = aux.n - 1;

        push(&stack, elem.m, elem.n);
    }
  }

  return -1;
}

int main()
{
    int x;
    x = ack(2,1);
    printf("%d ", x);
}
