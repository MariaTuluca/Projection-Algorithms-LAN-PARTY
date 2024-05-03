/*Implementati recursiv stergerea unei liste.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node;

Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(Node** head, int data)
{
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void displayList(Node* head)
{
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void deleteListRecursive(Node** head)
{
    if (*head == NULL)
        return;

    deleteListRecursive(&((*head)->next));
    free(*head);
    *head = NULL;
}

int main()
{
    Node* head = NULL;

    insertAtBeginning(&head, 7);
    insertAtBeginning(&head, 4);
    insertAtBeginning(&head, 2);
    insertAtBeginning(&head, 9);
    insertAtBeginning(&head, 1);

    printf("Lista initiala: ");
    displayList(head);

    deleteListRecursive(&head);

    printf("Lista dupa stergere: ");
    displayList(head); // Lista va fi goalã

    return 0;
}
