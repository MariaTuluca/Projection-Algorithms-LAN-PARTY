/*Inversati cuvintele dintr-o propozitie folosind o stiv�.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char word[100];
    struct Node* next;
}Node;

int isEmpty(Node *top){
    return top == NULL ;
}

void push(Node **top , const char *word)
{
    Node* newNode =(Node*)malloc(sizeof(Node));
    strcpy(newNode->word,word);
    newNode->next = *top;
    *top=newNode;
}

char* pop( Node **top)
{
    if ( isEmpty(*top)) return NULL ;

    Node *temp =(*top);
    *top =(*top)->next ;

    char* word = (char*)malloc(100*sizeof(char));
    strcpy(word, temp->word);

    free(temp);
    return word;
}

void reverseWord(char *sentence)
{
    Node* stack = NULL;

    char* word = strtok(sentence, " ");
    while(word != NULL)
    {
        push(&stack, word);
        word = strtok(NULL, " ");
    }

    while(!isEmpty(stack))
    {
        printf("%s ", pop(&stack));
    }
}

int main()
{
    char sentence[100];
    printf("Introduceti propozitia pe care o doriti: ");
    fgets(sentence, 100, stdin);

    if(strlen(sentence)>0 && sentence[strlen(sentence) - 1] == '\n')
    {
        sentence[strlen(sentence) - 1] = '\0'; //elimin ultimul caracter
    }

    printf("Propozitia inversata: ");
    reverseWord(sentence);
}
