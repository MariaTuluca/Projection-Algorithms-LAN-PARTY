#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void afisareMatrice(int mat[][5])
{
    for( int i = 0; i<5; ++i)
       {
           for( int j = 0; j<5; ++j)
        {
            printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
}

void afisareMedie(int mat[][5])
{
    for( int i = 0; i<5; ++i)
    {
        int suma = 0;

        for(int j = 0; j<5; ++j)
        {
            suma+=mat[i][j];
        }

       float media;
       media = suma/5;

        printf("\nMedia de pe linia %d: %f", i+1, media);

    }
}

int main(){

    int matrice[5][5];
    srand((time(0)));

    for( int i = 0; i<5; ++i)
        for( int j = 0; j<5; ++j)
        {
            matrice[i][j] = (rand()%201) - 100;
        }

    printf("Matricea initiala: \n");
    afisareMatrice(matrice);

    printf("\nMediile initiale:");
    afisareMedie(matrice);

    for( int i = 0; i<5; ++i)
    {
        int suma = 0;

        for(int j = 0; j<5; ++j)
        {
            suma+=matrice[i][j];;
        }

        float media;
        media = suma/5;

        for(int j = 0; j<5; ++j)
        {
            matrice[i][j] = matrice[i][j] - media;
        }

    }

    printf("\n\nMatricea finala: \n");
    afisareMatrice(matrice);

    printf("\nMediile finale:");
    afisareMedie(matrice);


}

