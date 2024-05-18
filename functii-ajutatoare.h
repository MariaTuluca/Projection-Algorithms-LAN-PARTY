// acest header conține apeluri de funcții ajutătoare
// pentru programul meu

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "liste.h"
#include "cozi.h"
#include "stive.h"

void datePlayer(FILE *f_date, Player **newPlayer);

void readDate(FILE *inputDate, Team **newTeam, ListOfPlayers **playerList);

void writeNamesOfTeams(ListOfTeams *teamList, FILE *fileOut);

void findTeamForElimination(ListOfTeams **teamList, ListOfTeams **eliminatedTeam);

float ScoreOfTeam(Team *team);

int max(int a, int b);

void remakeQueueOfMatches(Queue *matches, StackNode **winners, int *numberOfTeams);

void listOfThe8Finalists(QueueNode *matchNode, ListOfTeams **the8Finalists);

void populateQueue(Queue **matches, ListOfTeams *teamList);

void winnersAndLosersStacks(StackNode **winners, StackNode **losers, Queue *matches);

void writeWinnersFormated(StackNode *winners, FILE *fileOUT);