// acest fișier conține funcții ajutătoare
// pentru program, cum ar fi funcții de citire/scriere 
// în fișiere, pentru calculul maximelor, 

#include "functii-ajutatoare.h"
#include "liste.h"

//funcție pentru citire nume echipe
void readTeamName(FILE *f, Team **newTeam)
{
    char teamName[30];
    int i=1;

    if(fgets(teamName, sizeof(teamName), f) == NULL)
        printf("Eroare la citire nume echipa %d.", i++);
    else{ 
        int lung = strlen(teamName);
        while(lung>0 && (teamName[lung-1] == '\n'||teamName[lung-1] == '\r'||teamName[lung-1] == ' '))
            {
                teamName[--lung] = '\0';
            }

        *newTeam = malloc(sizeof(Team));
        if(*newTeam == NULL)
        {   printf("Eroare la alocare spatiu newTeam!");
            return 1;
        }

        (*newTeam)->name = malloc((strlen(teamName) + 1)*sizeof(char));
        if(*newTeam == NULL)
        {   printf("Eroare la alocare spatiu teamName!");
            return 1;
        }
        strcpy((*newTeam)->name, teamName);
        }
}

//functie suport pentru citire date fiecare player
void datePlayer(FILE *f_date, Player **newPlayer)
{
    char nume[30], prenume[30];
    int points;
    fscanf(f_date, "%s", nume);
    (*newPlayer)->lastName = malloc((strlen(nume) + 1)*sizeof(char));
        if((*newPlayer)->lastName == NULL)
        {   printf("Eroare la alocare spatiu last name(nume de familie) la player!");
            return 1;
        }

    fscanf(f_date, "%s", prenume);
    (*newPlayer)->firstName = malloc((strlen(prenume) + 1)*sizeof(char));
        if((*newPlayer)->firstName == NULL)
        {   printf("Eroare la alocare spatiu first name la player!");
            return 1;
        }

    strcpy((*newPlayer)->firstName, prenume);
    strcpy((*newPlayer)->lastName, nume);

    fscanf(f_date, "%d", &points);
    (*newPlayer)->points = points;
}

//funcție principală pentru citire date player
void readPlayers(FILE *file_date, ListOfPlayers **playerList, int nrPlayersOfTeam)
{
    for(int j=0; j<nrPlayersOfTeam; j++)
    {
        Player *newPlayer = malloc(sizeof(Player));
        if(newPlayer == NULL)
        {   printf("Eroare la alocare spatiu player!");
            return 1;
        }
//citim numele, prenumele și punctele pentru fiecare jucător, cu ajutorul unor funcții
//și apoi adăugăm player-ul la lista de players
        datePlayer(file_date, &newPlayer);
        addPlayerToList(playerList, newPlayer);
    }
}

//funcție pentu afișare nume echipe în fisierul de output
void writeNamesOfTeams(ListOfTeams *teamList, char *fileOut)
{
    FILE *f = fopen(fileOut, "wt");
    if(f == NULL)
    {   printf("Probleme la deschidere fisier de afișare nume echipe!");
        return 1;
    }
    while(teamList != NULL)
        {  char aux[30];
           strcpy(aux, teamList->team->name);
           fprintf(f, "%s \n", aux);
           teamList = teamList->next;
        }
        
    fclose(f);
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

        aux_teamList = aux_teamList->next;   //trec la analizarea urmatoarei echipe
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