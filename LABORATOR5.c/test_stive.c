#include"stive.h"

int main()
{
    Node* stack = NULL;

    int vector ={2, 4, 6, 8};

    for(int i=0; i<4; ++i)
    {
        push(&stack, i);
    }

    printStack(stack);
}
