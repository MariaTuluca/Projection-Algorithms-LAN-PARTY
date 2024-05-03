// acest header conține apeluri de funcții ajutătoare
// pentru program

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void readTeamName(FILE *f, Team **newTeam);

void datePlayer(FILE *f_date, Player **newPlayer);

void readPlayers(FILE *file_date, ListOfPlayers **playerList, int nrPlayersOfTeam);

void writeNamesOfTeams(ListOfTeams *teamList, char *fileOut);
