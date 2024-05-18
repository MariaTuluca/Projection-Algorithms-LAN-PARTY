#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//acest header este special pentru operații cu liste(adiacent și cozi)
#ifndef LISTE_H
#define LISTE_H
// structură de date - informații despre fiecare jucător
typedef struct Player {    
    char *firstName;
    char *secondName;
    int points;
}Player;

// structură de date - listă cu informații despre fiecare jucător
typedef struct ListOfPlayers {
    Player *player;
    struct ListOfPlayers *next;
}ListOfPlayers;

// structură de date - informații despre fiecare echipă
typedef struct Team {
    char *name;
    ListOfPlayers *players;
}Team;

// structură de date - listă cu informații despre fiecare echipă
typedef struct ListOfTeams {
    Team *team;
    struct ListOfTeams *next;
}ListOfTeams;

// structură de date - informații despre meciuri
typedef struct match{
    Team *team_1;
    Team *team_2;
}Match;

#endif

void addPlayerToList(ListOfPlayers **playerList, Player *player);

void addListOfPlayersToTeam(Team **newTeam, ListOfPlayers *playerList);

void addTeamToBegTeamList(ListOfTeams **teamList, Team *newTeam);

void freeListOfPlayers(ListOfPlayers **playerList);

void deleteTeam(ListOfTeams **teamList, ListOfTeams *eliminatedTeam);

void storeLastTeamsToList(ListOfTeams **finalList, Team *team);

void freeListOfTeams(ListOfTeams **teamList);

