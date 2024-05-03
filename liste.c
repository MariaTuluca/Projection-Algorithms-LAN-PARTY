#include "liste.h"

//acest fișier conține funcții specifice listelor

//funcție pentru adăugare player în listă
void addPlayerToList(ListOfPlayers **playerList, Player *player)
{
    ListOfPlayers *newNode = malloc(sizeof(ListOfPlayers));

    if(newNode == NULL)
    {   printf("Eroare la alocare spațiu newNode!");
        return 1;
    }
    newNode->player = player;
    if(*playerList == NULL)
    {   newNode->next = NULL;
        *playerList = newNode;
    }
    else{
            newNode->next = *playerList;
            *playerList = newNode;
        }
}