/*
Alocati dinamic spatiu pentru siruri de caractere. Utilizati functiile strlen, strcat,
strcmp, strcpy etc.
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
    int nrSiruri = 3;

    char** siruri = (char**)malloc(nrSiruri * sizeof(char*));
    if(siruri == NULL)
    {
        fprintf(stderr, "Eroare la alocarea sirurilor de caractere.");
        exit(1);
    }

    siruri[0] = (char*)malloc(20 * sizeof(char));
    siruri[1] = (char*)malloc(20 * sizeof(char));
    siruri[2] = (char*)malloc(20 * sizeof(char));

    if(siruri[0] == NULL || siruri[1] == NULL || siruri[2] == NULL)
    {
        fprintf(stderr, "Eroare la alocarea sirurilor individuale de caractere.");
        exit(1);
    }

    strcpy(siruri[0], "Mama");
    strcpy(siruri[1], " are ");
    strcpy(siruri[2], "mere.");

    strcat(siruri[0], siruri[1]);
    strcat(siruri[0], siruri[2]);
    int lungime = strlen(siruri[0]);


    printf("Rezultatul este: %s, cu lungimea de %d\n", siruri[0], lungime);

    if(strcmp(siruri[0], "Mama are mere.") == 0)
        printf("Concatenare reusita!");
    else printf("Fail la concatenare!");

    for(int i = 0; i<nrSiruri; ++i)
    {
        free(siruri[i]);
    }

    free(siruri);

    return 0;
}
