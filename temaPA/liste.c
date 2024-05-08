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

//funcție pentru adăugarea echipei formate la începutul listei de echipe
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

//funcție secundară pentru stocare date finaliști
void storeLastTeamsToList(ListOfTeams **finalList, Team *team)
{//creez echipă nouă și copiez toate datele
    Team *new_team = malloc(sizeof(Team));
    if(new_team == NULL)
    {   printf("Eroare la alocare spațiu new_team în storeLastTeamsToList!");
        return 1;
    } //numele echipei
    new_team->name = malloc(strlen(team->name) + 1);
    if(new_team->name == NULL)
    {   printf("Eroare la alocare spațiu new_team name în storeLastTeamsToList!");
        return 1;
    }
    strcpy(new_team->name, team->name);
    //players din echipă
    ListOfPlayers *aux_player = team->players;
    new_team->players = NULL;
    //parcurg lista de players și creez copii pentru fiecare jucător 
    while(aux_player != NULL)
    { // fiecare player
        Player *new_player = malloc(sizeof(Player));
        if(new_player == NULL)
    {   printf("Eroare la alocare spațiu new_player în storeLastTeamsToList!");
        return 1;
    }//primul și al doilea nume
        new_player->firstName = malloc(strlen(aux_player->player->firstName) + 1);
        if(new_player->firstName == NULL)
    {   printf("Eroare la alocare spațiu new_player firstName în storeLastTeamsToList!");
        return 1;
    }
        strcpy(new_player->firstName, aux_player->player->firstName);

        new_player->lastName = malloc(strlen(aux_player->player->lastName) + 1);
        if(new_player->lastName == NULL)
    {   printf("Eroare la alocare spațiu new_player lastName în storeLastTeamsToList!");
        return 1;
    }
        strcpy(new_player->lastName, aux_player->player->lastName);
    //points
        new_player->points = malloc(strlen(aux_player->player->points) + 1);
        //creez o listă nouă 
        ListOfPlayers *new_PlayerList = malloc(sizeof(ListOfPlayers));
        if(new_PlayerList == NULL)
    {   printf("Eroare la alocare spațiu new_PlayerList în storeLastTeamsToList!");
        return 1;
    }//copiem datele în listă
        new_PlayerList->player = new_player;
        new_PlayerList->next = new_team->players;
        new_team->players = new_PlayerList;
        //trec la următorul jucător
        aux_player = aux_player->next;
    }
    //adaug echipa la listă
    addTeamToTeamList(finalList, new_team);
}

//funcție principală recursivă pentru stocare date despre finaliști
void listOfThe8Finalists(QueueNode *matchNode, ListOfTeams **the8Finalists)
{//stocăm toate datele în lista finală
	storeLastTeamsToList(the8Finalists, matchNode->subject->team_1);
	storeLastTeamsToList(the8Finalists, matchNode->subject->team_2);

	if(matchNode->next != NULL)
		listOfThe8Finalists(the8Finalists, matchNode->next);
		
}

//funcție pentru umplere coadă cu meciuri
void populateQueue(Queue **matches, ListOfTeams *teamList)
{   //creez coada
    *matches = createQueue();
    //verific dacă am două echipe valabile pentru un nou meci
    for( ; teamList != NULL && teamList->next != NULL; teamList = teamList->next->next)
    {
        Match *new_match = malloc(sizeof(Match));
        if(new_match == NULL)
        {   printf("Eroare la alocare spațiu pentru un meci nou.\n");
            return 1;
        }
        //creez meciul nou și îl pun în coadă
        new_match->team_1 = teamList->team;
        new_match->team_2 = (teamList->next)->team;
        enQueue(*matches, new_match);
    }

}