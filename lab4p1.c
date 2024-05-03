/*Atunci când un sens de mers cu douã benzi se îngusteazã într-o
singurã bandã, traficul cel mai fluid se obtine prin metoda
fermoarului: masinile înainteazã alternativ de pe cele douã
benzi pe singura rãmasã. Implementati o functie care interclaseazã
douã liste cu elemente de tip int ce pot avea dimensiuni diferite.
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

    while(p!=NULL||d!=NULL)
    {
        if(p!=NULL){
            adaugaElement(&interclasata, p->val);
            p = p->next;
        }

        if(d!=NULL){
            adaugaElement(&interclasata, d->val);
            d = d->next;
        }
    }

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
