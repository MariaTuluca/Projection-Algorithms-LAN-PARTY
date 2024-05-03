#include"stive.h"

int* aleatoriu(int *vector)
{
    int elem, ok;

    for(int i=0; i<4; i++)
    {
        do{
            elem = (rand() % 4) + 1;

            int ok = 1;
            for(int j = 0; j<i; j++)
                if(vector[j] == elem) ok = 0;
        }while(ok==1);


        vector[i] = elem;
    }

    return vector;
}

Node* permutari(Node** in, int vector[])
{
    Node* out = NULL;
    Node* spur = NULL;

    int i = 0;
    int valoare_dorita = vector[i];

    while(!isEmpty(in))
    {
     int val = top(in);

     if(val == valoare_dorita)
        {
        pop(&in);
        push(&out, val);

        i++;
        if(i<4)
            valoare_dorita = vector[i];

        }

    else push(&spur, val);

    }

    if (!isEmpty(spur) && top(spur) == valoare_dorita)
            {
                pop(&spur);
                push(&out, valoare_dorita);
                i++;
                if (i < 4)
                    valoare_dorita = vector[i];
            }
    else {
                if (isEmpty(spur)) {
                    printf("Permutarea nu poate fi realizata.\n");
                    deleteStack(&out);
                    return NULL;
                } else {
                    printf("Permutarea nu poate fi realizata.\n");
                    deleteStack(&out);
                    deleteStack(&spur);
                    return NULL;
                }
            }

    deleteStack(&in);
    deleteStack(&spur);
    return out;
}

int main()
{
    Node* in = NULL;
    Node* out = NULL;

    for(int i=1; i<=4; ++i)
    {
        push(&in, i);
    }

    printf("\nVagoanele initiale:");
    printStack(in);

    int* vector =(int*)malloc(sizeof(int));
    vector = aleatoriu(vector);


    printf("\nVector aleatoriu:");
    for(int i=0; i<4; i++)
        printf("%d ", vector[i]);

    out = permutari(&in, vector);

    if (out != NULL)
    {
        printf("\nVagoanele in ordinea dorita de vector:");
        printStack(out);
    }

}
