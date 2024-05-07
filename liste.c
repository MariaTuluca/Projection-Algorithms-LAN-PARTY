#include "liste.h"

//acest fișier conține funcții specifice listelor

//funcție pentru adăugare player în listă
void addPlayerToList(ListOfPlayers **playerList, Player *player)
{
    ListOfPlayers *newNode = malloc(sizeof(ListOfPlayers));

    if(newNode == NULL)
    {   printf("Eroare la alocare spațiu newNode in addPlayerToList!");
        return 1;
    }
    //creez legăturile în lista de players
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

//funcție pentru adăugarea unei liste de players la echipa aferentă
void addListOfPlayersToTeam(Team **newTeam, ListOfPlayers *playerList)
{
    (*newTeam)->players = playerList;
}

//funcție pentru adăugarea echipei formate la finalul listei de echipe
void addTeamToTeamList(ListOfTeams **teamList, Team *newTeam)
{
    ListOfTeams *newNode = malloc(sizeof(ListOfTeams));
    if(newNode == NULL)
    {   printf("Eroare la alocare spațiu newNode in addTeamToTeamList!");
        return 1;
    }
    //creez legăturile în lista de teams
    newNode->team = newTeam;
    newNode->next = *teamList;
    *teamList = newNode;
}

//funcție pentru eliberarea memoriei ocupate de lista de players
void freeListOfPlayers(ListOfPlayers **playerList)
{
    while(*playerList != NULL)
    {   //creez un auxiliar în care rețin jucătorul
        ListOfPlayers *aux = *playerList;
        free(aux->player->firstName);
        free(aux->player->lastName);
        free(aux->player);
        free(aux);

        *playerList = (*playerList)->next;   //actualizez capătul listei
    }

}

//funcție pentru ștergere echipe (folosită de mine și la ștergerea echipei cu scorul cel mai mic)
void deleteTeam(ListOfTeams **teamList, ListOfTeams *eliminatedTeam)
{
    if(*teamList != eliminatedTeam)
    {
        ListOfTeams *aux = *teamList;
        while(aux->next != NULL)
        {
            if(aux->next == eliminatedTeam)
                   { aux->next = aux->next->next;
                     break;}   //dacă următoarea echipă este cea pe care dorim să o eliminăm, "trecem peste ea" și ieșim din buclă
            //dacă nu am găsit-o încă, trecem la următoarea echipă
            aux = aux->next;
        }
    }
    else{   //în cazul acesta, echipa de eliminat este chiar prima și "sărim" peste ea, actualizând lista principală
        *teamList = (*teamList)->next;
    }
    //includ cazul special în care listele sunt goale, în care nu se întâmplă nimic
    if(*teamList == NULL || eliminatedTeam == NULL)
            return;

    //eliberez memoria ocupată de echipa de eliminat, dar și de elementul listei
    free(eliminatedTeam->team->name);
    freeListOfPlayers(&(eliminatedTeam->team->players)); //trebuie să eliberez lista de players asociată
    free(eliminatedTeam->team);
    free(eliminatedTeam);
}

