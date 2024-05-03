/*Transformati o listã dublu înlãntuitã cu santinelã la final
într-o listã circularã.
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Elem{

    int val;
    struct Elem* next;
    struct Elem* prev;
}Node;

typedef struct{
    Node* head;
}Circulara;

Node* creeazaNode(int val)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
    {
        printf("Memorie insuficienta pt alocare 2!");
        exit(1);
    }

    newNode->val = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

Circulara* initializare()
{
    Circulara* lista = (Circulara*)malloc(sizeof(Circulara));
    if(lista == NULL)
    {
        printf("Memorie insuficienta pt alocare!\n");
        exit(1);
    }

    lista->head = creeazaNode(1);

    lista->head->next = lista->head;
    lista->head->prev = lista->head;

    return lista;
}

void adaugareLaFinal(Circulara* lista, int valoare)
{
    Node* newNode = creeazaNode(valoare);
    newNode->next = lista->head;
    newNode->prev = lista->head->prev;
    lista->head->prev->next = newNode;
    lista->head->prev = newNode;
}

void afiseaza(Circulara* lista)
{
    Node* current = lista->head->next;
    while(current != lista->head)
    {
        printf("%d ", current->val);
        current = current->next;
    }

}

void elibereaza(Circulara* lista)
{
    Node* current = lista->head->next;
    while(current != lista->head)
    {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(lista->head);
    free(lista);
}

int main()
{
    Circulara* lista = initializare();

    adaugareLaFinal(lista, 1);
    adaugareLaFinal(lista, 2);
    adaugareLaFinal(lista, 3);

    afiseaza(lista);

    elibereaza(lista);
}
