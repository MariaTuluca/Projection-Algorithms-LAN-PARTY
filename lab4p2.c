/*Scrieti o functie care interclaseazã douã liste cu elemente de
tip int. Fiecare listã are elementele în ordine crescãtoare.
Lista rezultatã trebuie sã fie de asemenea ordonatã si nu trebuie
sã continã duplicate. Solutia nu trebuie sã foloseascã memorie
suplimentarã fatã de cele douã liste.
*/

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
Node* interclasare(Node* prima, Node* aDoua)
{
    Node* interclasata = NULL;
    Node* p = prima;
    Node* d = aDoua;

    if(d == NULL) return prima;
    if(p == NULL) return aDoua;

    if(p->val < d->val)
    {
        interclasata = p;
        p = p->next;
    }
    else {interclasata = d;
        d = d->next;
        }

    Node* current = interclasata;

    while(p!=NULL&&d!=NULL)
    {
        if(p->val < d->val){
            current->next = p;
            p = p->next;
        }

        else if (d->val < p->val){
            current->next = d;
            d = d->next;
        }

        else {current->next = p;
              p = p->next;
              d = d->next;}

        current = current->next;
    }

    if(p!=NULL)
        current->next = p;


    if(d!=NULL)
        current->next = d;

    return interclasata;
}

int main()
{
  Node* prima = NULL;
  Node* aDoua = NULL;

  int nr1, nr2, valoare;

  printf("\nCate elemente doriti in prima lista? ");
  scanf("%d", &nr1);
  printf("\nCate elemente doriti in a doua lista? ");
  scanf("%d", &nr2);

  printf("\nElementele primei liste: ");
  for(int i =0; i<nr1; i++){
    scanf("%d", &valoare);
    adaugaElement(&prima, valoare);
  }

  printf("\nElementele celei de a doua liste: ");
  for(int i =0; i<nr2; i++){
    scanf("%d", &valoare);
    adaugaElement(&aDoua, valoare);
  }

  printf("\nPrima lista: ");
  afisareLista(prima);
  printf("\nA doua lista: ");
  afisareLista(aDoua);

  Node* interclasata = interclasare(prima, aDoua);
  printf("\nLista interclasata: ");
  afisareLista(interclasata);

}
