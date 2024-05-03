/*Implementati o listã dublu înlãntuitã cu santinelã la final.
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
    Node* tail;
}ListaDubluInlantuita;

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

ListaDubluInlantuita* initializare()
{
    ListaDubluInlantuita* lista = (ListaDubluInlantuita*)malloc(sizeof(ListaDubluInlantuita));
    if(lista == NULL)
    {
        printf("Memorie insuficienta pt alocare!\n");
        exit(1);
    }

    lista->head = creeazaNode(1);
    lista->tail = creeazaNode(1);

    lista->head->next = lista->tail;
    lista->tail->prev = lista->head;

    return lista;
}

void adaugareLaFinal(ListaDubluInlantuita* lista, int valoare)
{
    Node* newNode = creeazaNode(valoare);
    newNode->prev = lista->tail->prev;
    newNode->next = lista->tail;
    lista->tail->prev->next = newNode;
    lista->tail->prev = newNode;
}

void afiseaza(ListaDubluInlantuita* lista)
{
    Node* current = lista->head->next;
    while(current != lista->tail)
    {
        printf("%d ", current->val);
        current = current->next;
    }

}

void elibereaza(ListaDubluInlantuita* lista)
{
    Node* current = lista->head;
    Node* next;

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(lista);
}

int main()
{
    ListaDubluInlantuita* lista = initializare();

    adaugareLaFinal(lista, 1);
    adaugareLaFinal(lista, 2);
    adaugareLaFinal(lista, 3);

    afiseaza(lista);

    elibereaza(lista);
}
