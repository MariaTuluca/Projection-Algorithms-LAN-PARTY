// acest fișier conține funcții ajutătoare
// pentru program, cum ar fi funcții de citire/scriere 
// în fișiere, pentru calculul maximelor, pentru toate structurile

#include "functii-ajutatoare.h"

//functie suport pentru citire date fiecare player
void datePlayer(FILE *f_date, Player **newPlayer)
{
    char nume[30], prenume[30];
    int points;

    fscanf(f_date, "%s", nume);
    fscanf(f_date, "%s", prenume);
    fscanf(f_date, "%d", &points);

    (*newPlayer)->firstName = malloc((strlen(nume) + 1)*sizeof(char));
        if((*newPlayer)->firstName == NULL)
        {   printf("Eroare la alocare spatiu last name(nume de familie) la player!");
            return;
        }
    (*newPlayer)->secondName = malloc((strlen(prenume) + 1)*sizeof(char));
        if((*newPlayer)->secondName == NULL)
        {   printf("Eroare la alocare spațiu first name la player!");
            return;
        }

    strcpy((*newPlayer)->firstName, prenume);
    strcpy((*newPlayer)->secondName, nume);
    (*newPlayer)->points = points;
    //ignor linia dintre echipe
    fscanf(f_date, "\n");
}

//funcție principală pentru citire date din fișier
void readDate(FILE *inputDate, Team **newTeam, ListOfPlayers **playerList)
{
    int nrPlayersOfTeam;
    fscanf(inputDate, "%d", &nrPlayersOfTeam);
    fgetc(inputDate);

    char teamName[30];
    int i=1;

    if(fgets(teamName, sizeof(teamName), inputDate) == NULL)
        printf("Eroare la citire nume echipa %d.", i++);
    else{//creez numele echipei, având în vedere că pot întâlni mai multe caractere space
        int lung = strlen(teamName);
        while(lung>0 && (teamName[lung-1] == '\n' || teamName[lung-1] == '\r'|| teamName[lung-1] == ' '))
            {//verific ultimul caracter din nume și îl actualizez
                teamName[--lung] = '\0';
            }
        //atribui numele
        *newTeam = malloc(sizeof(Team));
        if(*newTeam == NULL)
        {   printf("Eroare la alocare spatiu newTeam!");
            return;
        }
        (*newTeam)->name = malloc((strlen(teamName) + 1)*sizeof(char));
        if(*newTeam == NULL)
        {   printf("Eroare la alocare spatiu teamName!");
            return;
        }
        strcpy((*newTeam)->name, teamName);
        }

     for(int j=0; j<nrPlayersOfTeam; j++)
    {
        Player *newPlayer = malloc(sizeof(Player));
        if(newPlayer == NULL)
        {   printf("Eroare la alocare spatiu player!");
            return;
        }
    //citim numele, prenumele și punctele pentru fiecare jucător, cu ajutorul unor funcții
    //și apoi adăugăm player-ul la lista de players
        datePlayer(inputDate, &newPlayer);
        addPlayerToList(playerList, newPlayer);
    }
    fgetc(inputDate); 
}

//funcție pentu afișare nume echipe în fisierul de output
void writeNamesOfTeams(ListOfTeams *teamList, FILE *fileOut)
{
    while(teamList != NULL)
        {  char auxName[30];
           strcpy(auxName, teamList->team->name);
           fprintf(fileOut, "%s \n", auxName);
           teamList = teamList->next;
        }

}

//funcție pentru determinarea echipelor eligibile pentru eliminare
void findTeamForElimination(ListOfTeams **teamList, ListOfTeams **eliminatedTeam)
{
    ListOfTeams *aux_teamList = *teamList;
    *eliminatedTeam = NULL;
    float min_score = 1000.00;

    //pentru fiecare echipă din lista de echipe, calculez numărul total de puncte și media
    while(aux_teamList != NULL)
    {
        Team *team = aux_teamList->team;
        if(team != NULL)
        {
            int total_points=0;
            int numberOfPlayers = 0;
            //folosindu-mă de listă, trec pe la fiecare player pentru a lua în considerare punctele lui
            ListOfPlayers *aux_playerList = team->players;
            while(aux_playerList != NULL)
            {
                total_points += aux_playerList->player->points;
                numberOfPlayers++;
                aux_playerList = aux_playerList->next;
            }

            //calculez media pentru echipa curenta
            float avgTeam_score = (float)total_points/numberOfPlayers;
            if(min_score > avgTeam_score)
                { min_score = avgTeam_score;
                *eliminatedTeam = aux_teamList;
                }
        }

        aux_teamList = aux_teamList->next;   //trec la analizarea următoarei echipe
    }    
}

float ScoreOfTeam(Team *team)
{//asemănătoare cu "if"-ul din funcția de mai sus
    if(team != NULL)
        {
            int total_points=0;
            int numberOfPlayers = 0;
            //folosindu-mă de listă, trec pe la fiecare player pentru a lua în considerare punctele lui
            ListOfPlayers *aux_playerList = team->players;
            while(aux_playerList != NULL)
            {
                total_points += aux_playerList->player->points;
                numberOfPlayers++;
                aux_playerList = aux_playerList->next;
            }

            //calculez media pentru echipa curenta
            float avgTeam_score = (float)total_points/numberOfPlayers;
            return avgTeam_score;
        }
    else return 0;
}

//funcție pentru max
int max(int a, int b)
{
    return ((a>b)?a:b);
}

//funcție pentru refacerea cozii de meciuri
void remakeQueueOfMatches(Queue *matches, StackNode **winners, int *numberOfTeams)
{//inițializez numărul de teams din stivă cu 0
    *numberOfTeams = 0;

    while(!isStackEmpty(*winners))
    {//creez un nou match
        Match *new_match = malloc(sizeof(Match));
        if(new_match == NULL)
        {   printf("Eroare la alocare spațiu new_match!");
            return;
        }
        (*numberOfTeams)++;
        //prima și a doua echipă din stiva winners vor forma un nou match 
        Team *team1 = pop(winners);
        if((*winners)->next != NULL)
            {   (*numberOfTeams)++;
                Team *team2 = pop(winners);
                new_match->team_1 = team1;
                new_match->team_2 = team2;
            }
        //adaug meciul în coadă
        enQueue(matches, new_match);
    }
}

//funcție principală recursivă pentru stocare date despre finaliști
void listOfThe8Finalists(QueueNode *matchNode, ListOfTeams **the8Finalists)
{//stocăm toate datele, adică fiecare echipă din meciurile rămase în lista finală
	storeLastTeamsToList(the8Finalists, matchNode->subject->team_1);
	storeLastTeamsToList(the8Finalists, matchNode->subject->team_2);

	if(matchNode->next != NULL)
		listOfThe8Finalists(matchNode->next, the8Finalists);
}

//funcție pentru umplere coadă cu meciuri
void populateQueue(Queue **matches, ListOfTeams *teamList)
{   //creez coada
    *matches = createQueue();
    //verific dacă am două echipe valabile pentru meci nou
    for( ; teamList != NULL && teamList->next != NULL; teamList = teamList->next->next)
    {
        Match *new_match = malloc(sizeof(Match));
        if(new_match == NULL)
        {   printf("Eroare la alocare spațiu pentru un meci nou.\n");
            return;
        }
        //creez meciul nou și îl pun în coadă(prima și a doua echipă din listă)
        new_match->team_1 = teamList->team;
        new_match->team_2 = (teamList->next)->team;
        enQueue(*matches, new_match);
    }

}

//funcție pentru creare stive de winners și de losers
void winnersAndLosersStacks(StackNode **winners, StackNode **losers, Queue *matches)
{
	Team *teamWin = NULL;
    Team *teamLose = NULL;

	while(!isQueueEmpty(matches))
	{//prelucrez primul meci din coadă
		Match *aux_match = deQueue(matches);
        if(aux_match == NULL)
            {printf("Eroare la deQueue.\n");
            return;}

		float avgTeam1 = ScoreOfTeam(aux_match->team_1), avgTeam2 = ScoreOfTeam(aux_match->team_2);

		if(avgTeam2 <= avgTeam1)    //câștigă prima echipă
		{teamWin = aux_match->team_1;
		 teamLose = aux_match->team_2;
		}
		else    //câștigă a doua echipă
		{teamLose = aux_match->team_1;
		 teamWin = aux_match->team_2;
		}	

		push(winners, teamWin);
		push(losers, teamLose);

		free(aux_match);
	}
}

//funcție pentru afișare echipe câștigătoare în fișier, cu regulile din cerință
void writeWinnersFormated(StackNode *winners, FILE *fileOUT)
{
	while(winners != NULL)
		{
			float score = ScoreOfTeam(winners->subject);
			fprintf(fileOUT, "%-34s-  %.2f\n", winners->subject->name, score);
			winners = winners->next;
		}
}


