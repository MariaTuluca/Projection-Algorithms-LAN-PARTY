/*Creati o functie care sterge dintr-o listã al k-lea element
începând cu sfârsitul acesteia. Complexitatea solutiei trebuie
sã fie O(n).*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Elem{

    int val;
    struct Elem* next;
}Node;

void afisareLista(Node *head)
{
    while(head != NULL)
    {
        printf("%d ",head->val);
        head = head->next;
    }
}

void adaugaInceput(Node **head, int valoare)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = valoare;
    newNode->next = *head;
    *head = newNode;
}

void adaugaElement(Node **head, int valoare)
{
    Node *aux = *head;
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->val = valoare;

    if(*head == NULL)
        adaugaInceput(&*head, valoare);
    else {
            while(aux->next!=NULL)
                aux = aux->next;

            aux->next = newNode;
            newNode->next = NULL;

         }
}

Node* stergeElement(Node **lista, int poz)
{
    Node *slow = *lista;
    Node *fast = *lista;

    for(int i = 0; i<poz && fast!=NULL; i++)
    {
        fast = fast->next;
    }

    if(fast == NULL)
    {
        printf("Lista nu are suficiente elemente..");
        return *lista;
    }

    if(fast->next == NULL) //inseamna ca primul element este al k-lea de la coada
    {
        *lista = slow->next;
        free(slow);
        return *lista;
    }

    while(fast->next != NULL) //duc slow pe pozitia k de la capat
    {
        slow = slow->next;
        fast = fast->next;
    }

    Node *sters = slow->next;
    slow->next = slow->next->next;

    free(sters);

    return *lista;
}

int main()
{
  Node* lista = NULL;

  int nr, valoare;

  printf("\nCate elemente doriti in lista? ");
  scanf("%d", &nr);

  printf("\nElementele listei: ");
  for(int i =0; i<nr; i++){
    scanf("%d", &valoare);
    adaugaElement(&lista, valoare);
  }

  printf("\nLista: ");
  afisareLista(lista);

  int k;
  printf("\nAl cate-lea element de la coada doriti sa stergeti?");
  scanf("%d", &k);

  Node* listaStearsa = stergeElement(&lista, k);
  printf("\nLista noua: ");
  afisareLista(listaStearsa);

}
