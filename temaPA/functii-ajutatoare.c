// acest fișier conține funcții ajutătoare
// pentru program, cum ar fi funcții de citire/scriere 
// în fișiere, pentru calculul maximelor, 

#include "functii-ajutatoare.h"
#include "liste.h"

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

void datePlayer(FILE *f_date, Player **newPlayer)
{
    char nume[30], prenume[30];
    int points;
        fscanf(f_date, "%s", nume);
        (*newPlayer)->firstName = malloc((strlen(nume) + 1)*sizeof(char));
        if((*newPlayer)->firstName == NULL)
        {   printf("Eroare la alocare spatiu first name la player!");
            return 1;
        }
        (*newPlayer)->lastName = malloc((strlen(prenume) + 1)*sizeof(char));
        if((*newPlayer)->firstName == NULL)
        {   printf("Eroare la alocare spatiu second name la player!");
            return 1;
        }

        strcpy((*newPlayer)->firstName, nume);
        strcpy((*newPlayer)->lastName, prenume);

        fscanf(f_date, "%d", &points);
        (*newPlayer)->points = points;
}

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

