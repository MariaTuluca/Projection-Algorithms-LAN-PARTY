#include "liste.h"

//acest fișier conține funcții specifice listelor

//funcție pentru adăugare player în listă
void addPlayerToList(ListOfPlayers **playerList, Player *player)
{//verific dacă lista este goală
    if(*playerList != NULL)
    { //parcurg până la final lista
    ListOfPlayers *newList = *playerList;
    while(newList->next != NULL)
        {newList = newList->next;}

    newList->next = malloc(sizeof(ListOfPlayers));
    if(newList->next == NULL)
    {   printf("Eroare la alocare spațiu newList nou element in addPlayerToList!");
        return;
    }
    //creez legătura în lista de players
    newList->next->player = player;
    newList->next->next = NULL;
    }
    else{
    *playerList = malloc(sizeof(ListOfPlayers));
    if(playerList == NULL)
    {   printf("Eroare la alocare spațiu lista in addPlayerToList!");
        return;
    }
    //introduc player-ul în listă
    (*playerList)->player = player;
    (*playerList)->next = NULL;
    }    
}

//funcție pentru adăugarea unei liste de players la echipa aferentă
void addListOfPlayersToTeam(Team **newTeam, ListOfPlayers *playerList)
{
    (*newTeam)->players = playerList;
}

//funcție pentru adăugarea echipei formate la începutul listei de echipe
void addTeamToBegTeamList(ListOfTeams **teamList, Team *newTeam)
{
    ListOfTeams *newNode = malloc(sizeof(ListOfTeams));
    if(newNode == NULL)
    {   printf("Eroare la alocare spațiu newNode in addTeamToTeamList!");
        return;
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
        free(aux->player->secondName);
        free(aux->player);

        *playerList = (*playerList)->next;   //actualizez capătul listei
        free(aux);
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
        return;
    } //numele echipei
    new_team->name = malloc(strlen(team->name) + 1);
    if(new_team->name == NULL)
    {   printf("Eroare la alocare spațiu new_team name în storeLastTeamsToList!");
        return;
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
        return;
    }//primul și al doilea nume
        new_player->firstName = malloc(strlen(aux_player->player->firstName) + 1);
        if(new_player->firstName == NULL)
    {   printf("Eroare la alocare spațiu new_player firstName în storeLastTeamsToList!");
        return;
    }
        new_player->secondName = malloc(strlen(aux_player->player->secondName) + 1);
        if(new_player->secondName == NULL)
    {   printf("Eroare la alocare spațiu new_player secondName în storeLastTeamsToList!");
        return;
    }       
        strcpy(new_player->firstName, aux_player->player->firstName);
        strcpy(new_player->secondName, aux_player->player->secondName);
        //points
        new_player->points = aux_player->player->points;
        //creez o listă nouă 
        ListOfPlayers *new_PlayerList = malloc(sizeof(ListOfPlayers));
        if(new_PlayerList == NULL)
    {   printf("Eroare la alocare spațiu new_PlayerList în storeLastTeamsToList!");
        return;
    }//copiez datele în listă
        new_PlayerList->player = new_player;
        new_PlayerList->next = new_team->players;
        new_team->players = new_PlayerList;
        //trec la următorul jucător
        aux_player = aux_player->next;
    }
    //adaug echipa la listă
    addTeamToBegTeamList(finalList, new_team);
}

//funcție pentru eliberare spațiu ocupat de lista de echipe
void freeListOfTeams(ListOfTeams **teamList)
{
    while(*teamList != NULL)
    {   //creez un auxiliar în care rețin jucătorul
        free((*teamList)->team->name);  //eliberez numele
        freeListOfPlayers(&(*teamList)->team->players);  //apoi lista de players
        free(*teamList); //apoi chiar lista
        *teamList = NULL;  //good practice
        
        *teamList = (*teamList)->next;   //actualizez capătul listei
    }
}