/*
Definiti o structurã de date student care contine urmãtoarele câmpuri:
struct student {
char *nume , * prenume ;
int id; // id student
float note [5]; // notele obtinute in semestrul anterior
};
Declarati un vector studenti alocat dinamic care contine elemente de tip student.
Scrieti câte o functie pentru
a. Alocarea spatiului pentru vector.
b. Citirea datelor (de la tastaturã) pentru o variabilã de tip student.
c. Calculul numãrului de restante pentru un student.
d. Stergerea din vector a studentilor care au cel putin o restantã, cu realocarea
spatiului pentru vector.
e. Adãugarea unui student nou, pe o anumitã pozitie (cititã de la tastaturã), cu
realocarea spatiului.
f. Afisarea datelor pentru un student: cele din structurã si numãrul de restante.
Apelati în main functiile de mai sus si testati functionarea.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    char *nume, *prenume;
    int id;
    float note[5];
}Student;

Student* alocareVector(int nrStud)
{
    Student* vector = (Student*)malloc(nrStud * sizeof(Student));
    if(vector == NULL)
    {
        fprintf(stderr, "Eroare la alocarea vectorului de studenti.");
        exit(1);
    }

    return vector;
}

Student* citireStudent(Student* s)
{
    printf("Introduceti numele studentului: ");
    s->nume = (char*)malloc(50 * sizeof(char));
    scanf("%s", s->nume);

    printf("Introduceti prenumele studentului: ");
    s->prenume = (char*)malloc(50 * sizeof(char));
    scanf("%s", s->prenume);

    printf("Introduceti id-ul studentului: ");
    scanf("%d", &s->id);

    printf("Introduceti notele studentului: ");
    for(int i = 0; i<5; ++i)
    {
        scanf("%f", &s->note[i]);
    }
}

int numarRestante(Student* s)
{
    int restante = 0;
    for(int i = 0; i<5; ++i)
    {
        if(s->note[i] < 5.0) restante++;
    }

    return restante;
}

void afisareStudent(Student* s)
{
    printf("Nume student:%s\n", s->nume);
    printf("Prenume student:%s\n", s->prenume);
    printf("ID student:%d\n", s->id);
    printf("Note: ");
        for(int i = 0; i<5; ++i)
        {
            printf("%.2f ", s->note[i]);
        }
    printf("\nNumar restante: %d\n", numarRestante(s));
}

Student* stergereStudentiRestantieri(Student* vector, int* nrStd)
{
    Student* vectorNou = (Student*)malloc(*nrStd * sizeof(Student));
    if(vectorNou == NULL)
    {
        fprintf(stderr, "Eroare la alocarea vectorului nou.");
        exit(1);
    }

    int index = 0;
    for(int i = 0; i<*nrStd; ++i)
    {
        if(numarRestante(&vector[i]) == 0)
            vectorNou[index++] = vector[i];

        else {free(vector[i].nume);
              free(vector[i].prenume);
             }
    }

    *nrStd = index;
    return vectorNou;
}

Student* adaugareStudent(Student* vector, int* numarStudenti, int pozitie)
{
    Student* vectorNou = (Student*)realloc(vector, (*numarStudenti + 1) * sizeof(Student));
    if(vectorNou == NULL)
    {
        fprintf(stderr, "Eroare la realocarea vectorului pentru adaugarea unui student.");
        exit(1);
    }

    *numarStudenti += 1;

    for(int i = *numarStudenti - 1; i > pozitie; --i)
    {
        vectorNou[i] = vectorNou[i - 1];
    }

    printf("Adaugare student nou pe pozitia %d: \n", pozitie);
    citireStudent(&vectorNou[pozitie]);

    return vectorNou;
}

void afisareVectorStudenti(Student* vector, int numar)
{
    printf("Vector studenti: \n");
    for(int i = 0; i<numar; ++i)
    {
        printf("Student %d: \n", i+1);
        afisareStudent(&vector[i]);
        printf("\n");
    }
}

int main()
{
    int nrStudenti;

    printf("Introdu un numar de studenti:\n");
    scanf("%d", &nrStudenti);

    Student* vectorStudenti = alocareVector(nrStudenti);

    for(int i = 0; i<nrStudenti; ++i)
    {
        printf("Citire date pentru studentul %d:\n", i+1);
        citireStudent(&vectorStudenti[i]);
    }

    printf("Vector initial de studenti:\n");
    afisareVectorStudenti(vectorStudenti, nrStudenti);

    int std;
    printf("Carui student doriti sa ii calculati restantele?");
    scanf("%d", &std);
    printf("Numarul de restante pentru studentul %d: %d\n", std, numarRestante(&vectorStudenti[std-1]));

    vectorStudenti = stergereStudentiRestantieri(vectorStudenti, &nrStudenti);

    printf("\nVector dupa stergerea studentilor cu restante: \n");
    afisareVectorStudenti(vectorStudenti, nrStudenti);

    int pozitieNoua;
    printf("Introduceti pozitia pentru adaugarea studentului nou: ");
    scanf("%d", &pozitieNoua);

    vectorStudenti = adaugareStudent(vectorStudenti, &nrStudenti, pozitieNoua);
    printf("\nVector dupa adaugarea studentului nou: \n");
    afisareVectorStudenti(vectorStudenti, nrStudenti);

    for(int i = 0; i<nrStudenti; ++i)
    {
        free(vectorStudenti[i].nume);
        free(vectorStudenti[i].prenume);
    }

    free(vectorStudenti);

    return 0;
}
