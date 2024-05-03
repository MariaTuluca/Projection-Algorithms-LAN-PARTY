/*
Alocati dinamic spatiu pentru o variabilã numar complex, un vector/matrice de
numere complexe, unde numar complex este o structurã.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    double real;
    double imaginar;
}Complex;

Complex* alocareComplex()
{
    Complex* numarComplex = (Complex*)malloc(sizeof(Complex));

    if(numarComplex == NULL)
    {
        fprintf(stderr, "Eroare la alocarea numarului complex.");
        exit(1);
    }

    return numarComplex;
}

Complex* alocareVector(int dimensiune)
{
    Complex* vector = (Complex*)malloc(dimensiune * sizeof(Complex));
    if(vector == NULL)
    {
        fprintf(stderr, "Eroare la alocarea vectorului complex.");
        exit(1);
    }

    return vector;
}

Complex** alocareMatrice( int linii, int coloane)
{
    Complex** matrice = (Complex**)malloc(linii * sizeof(Complex*));
    if(matrice == NULL)
    {
        fprintf(stderr, "Eroare la alocarea matricei complexe.");
        exit(1);
    }

    for( int i = 0; i<linii; ++i)
    {
        matrice[i] = (Complex*)malloc(coloane * sizeof(Complex));

        if(matrice[i] == NULL)
        {
         fprintf(stderr, "Eroare la alocarea matricei complexe 2.");
         exit(1);
        }
    }

    return matrice;
}

int main()
{
    Complex* numarComplex = alocareComplex();

    int dimVector = 6;
    Complex* vectorComplex = alocareVector(dimVector);

    int liniiMatrice = 3;
    int coloaneMatrice = 4;
    Complex** matriceComplex = alocareMatrice(liniiMatrice, coloaneMatrice);

    free(numarComplex);
    free(vectorComplex);
    for( int i; i<liniiMatrice; ++i)
        free(matriceComplex[i]);

    free(matriceComplex);

    return 0;
}
