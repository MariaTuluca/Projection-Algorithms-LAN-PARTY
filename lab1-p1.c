/*
Alocati dinamic spatiu pentru o matrice de întregi de dimensiune (l x c). Realocati
apoi spatiul pentru dimensiunea ((l+1) x c). Alegeti functia de alocare astfel încât
sã nu fie necesarã o procedurã de initializare cu 0 a elementelor matricii.
*/

#include<stdio.h>
#include<stdlib.h>

int** realocare(int** matrice, int l, int c)
{
    int** matriceNoua = (int**)realloc(matrice, (l + 1) * sizeof(int*));
    if(matriceNoua == NULL)
    {
        fprintf(stderr, "Eroare la alocarea matricei.");
        exit(1);
    }

    matriceNoua[l] = (int*)malloc(c * sizeof(int));
    if(matriceNoua[l] == NULL)
    {
        fprintf(stderr, "Eroare la alocarea matricei.");
        exit(1);
    }

    return matriceNoua;
}

int main()
{
    int l=3, c=4;

    int** matrice = (int**)malloc(l * sizeof(int*));

    if(matrice == NULL)
    {
        fprintf(stderr, "Eroare la alocarea matricei.");
        exit(1);

    }

    for( int i = 0; i<l; ++i)
    {
        matrice[i] = (int*)malloc(c * sizeof(int));
        if(matrice[i] == NULL)
        {
            fprintf(stderr, "Eroare la alocarea matricei.");
            exit(1);
        }
    }

    matrice = realocare(matrice, l, c);

    printf("Dimensiunea matricei noi: (%d x %d)\n", l+1, c);

    for( int i = 0; i<= l; ++i)
    {
        free(matrice[i]);
    }
    free(matrice);

    return 0;
}
