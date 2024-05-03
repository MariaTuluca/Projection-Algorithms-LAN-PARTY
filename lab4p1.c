/*Atunci c�nd un sens de mers cu dou� benzi se �ngusteaz� �ntr-o
singur� band�, traficul cel mai fluid se obtine prin metoda
fermoarului: masinile �nainteaz� alternativ de pe cele dou�
benzi pe singura r�mas�. Implementati o functie care interclaseaz�
dou� liste cu elemente de tip int ce pot avea dimensiuni diferite.
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
