#include<stdio.h>
#include<stdlib.h>

int* pointerMinim(int vector[], int dim)
{
    int minim = vector[0];
    int pozitie = 0;

    for( int i=1; i<dim; i++)
        {
            if(vector[i] < minim) {pozitie = i;
                                   minim = vector[i];
                                  }
        }

    return &vector[pozitie];
}

int* stergere(int vector[], int* dim)
{
    int* pozitie = pointerMinim(vector, *dim);

    for( int i=0; i<*dim; i++)
    {
        if(&vector[i] == pozitie)
            {
            for( int j = i; j< *dim - 1; ++j)
                        vector[j] = vector[j+1];

            (*dim)--;

            vector = (int*)realloc(vector, (*dim)*sizeof(int));
            break;
            }
    }

    return vector;
}
int main(){

    int *vector = (int*)malloc(10 * sizeof(int));
    int dim = 0;

    do
    {
        printf("vector[%d] = ", dim);
        scanf("%d", &vector[dim]);

    }while(vector[dim++] != 0);

    dim--;

    printf("Dimensiunea %d\n Vectorul initial:", dim);
    for(int i =0; i<dim; ++i)
    {
        printf("%d ", vector[i]);
    }

    int* minim = pointerMinim(vector, dim);
    printf("\nAdresa minimului din vector: %p, Valoarea minima din vector: %d\n", minim, *minim);

    vector = stergere(vector, &dim);

    printf("Dimensiunea: %d\n Vectorul final:", dim);
    for(int i =0; i<dim; ++i)
    {
        printf("%d ", vector[i]);
    }

    free(vector);
}
