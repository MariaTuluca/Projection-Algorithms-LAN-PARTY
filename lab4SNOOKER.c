
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct element {
    int val;
    struct element *next;
};

typedef struct element node;

//adauga un nou element cu o valoare specificata la inceputul unei liste
void add_val_at_beg(node **head, int v)
{
	node *newNode = (node*)malloc(sizeof(node));
	newNode->val = v;
	newNode->next = *head;
	*head = newNode;
}

//adauga un nou element cu o valoare specificata la sfarsitul unei liste
void add_val_at_end(node **head, int v)
{
	node *newNode = (node*)malloc(sizeof(node));
	newNode->val = v;

	if (*head == NULL)
        add_val_at_beg(&*head, v);
	else
    {
        node *aux = *head;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = newNode;
		newNode->next = NULL;
	}
}

//ia primul nod din bile si il ataseaza la sfarsitul listei meci
//capatul initial al lui bile devine bile->next
void add_existing_node_at_end(node **head, node **bile)
{
	if (*head == NULL)
    {
        *head = *bile;
        *bile = (*bile)->next;
        (*head)->next = NULL;
	}
	else
    {
	    node *aux = *head;

		while (aux->next!=NULL)
			aux = aux->next;

		aux->next = *bile;
		*bile = (*bile)->next;
		(aux->next)->next = NULL;
	}
}

//cauta un element cu o anumita valoare si returneaza adresa lui dintr-o lista
node* cauta(node *head, int v)
{
    node *aux = head;

    while(aux != NULL)
    {
        if(aux->val == v)
            return aux;

        aux = aux->next;
    }

    return NULL;
}

//sterge un element cu o valoare specificata
void delete_node_with_val(node **head, int v)
{
	node *aux = *head;

	if (aux->val == v)
    {
		*head = (*head)->next;
		free(aux);
		return;
	}

	node *prev = *head;

	while (aux != NULL)
		if(aux->val != v)
        {
			prev = aux;
			aux = aux->next;
		}
		else
        {
			prev->next = aux->next;
			free(aux);
			return;
		}
}

//afiseaza elementele unei liste
void print_list(node *head)
{
    if(head == NULL){
        printf("lista goala\n");
        printf("---------\n");
        return;
    }

    while(head != NULL)
    {
        printf("%d %p\n", head->val, head);
        head = head->next;
    }
    printf("---------\n");
}

//simulare joc snooker cu liste
int main()
{
    node *bile = NULL;
    node *meci = NULL;

    int colorate[6] = {2, 3, 4, 5, 6, 7};

    for(int i = 1; i <= 15; i++)
        add_val_at_end(&bile, 1);

    for(int i = 0; i < 6; i++)
        add_val_at_end(&bile, colorate[i]);

    srand(time(NULL));

    print_list(bile);

    while(bile->val == 1){
        add_existing_node_at_end(&meci, &bile);

        int p = rand() % 6;

        node *x = cauta(bile, colorate[p]); //pune colorate random in meci
        add_val_at_end(&meci, x->val);
    }

    for(int i = 0; i < 6; i++){
        add_val_at_end(&meci, colorate[i]); //le pune in ordine la final in meci
        delete_node_with_val(&bile, colorate[i]);
    }

    print_list(bile);
    print_list(meci);

    return 0;
}
