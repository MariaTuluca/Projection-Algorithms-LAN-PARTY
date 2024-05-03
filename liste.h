#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//acest header este special pentru operații cu liste

// structură de date - informații despre fiecare jucător
typedef struct Player {    
    char *firstName;
    char *lastName;
    int points;
}Player;

// structură de date - informații despre fiecare echipă
typedef struct Team {
    char *name;
    ListOfPlayers *players;
}Team;

// structură de date - listă cu informații despre fiecare jucător
typedef struct ListOfPlayers {
    Player *player;
    struct ListOfPlayers *next;
}ListOfPlayers;

// structură de date - listă cu informații despre fiecare echipă
typedef struct ListOfTeams {
    Team *team;
    struct ListOfTeams *next;
}ListOfTeams;

void addPlayerToList(ListOfPlayers **playerList, Player *player);

void addListOfPlayersToTeam(Team **newTeam, ListOfPlayers *playerList);

void addTeamToTeamList(ListOfTeams **teamList, Team *newTeam);
