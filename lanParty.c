#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player
{
    char* firstName;
    char* lastName;
    int points;
} Player;

int main(int argc, char* argv[])
{
    char *input = argv[1];
    char *output = argv[2];

    FILE *fisierIN = fopen(input, "r");
    if(fisierIN == NULL)
        {
            printf("Fisierul 'd.in' nu poate fi deschis.\n");
            return 1;
        }

    int numberOfTeams;
    fscanf(fisierIN, "%d", &numberOfTeams);

    for(int i = 0; i<3; i++)
    {
        int nrPlayers;
        char nameTeam[100];
        fscanf(fisierIN, "%d", &nrPlayers);
        fgets(nameTeam, sizeof(nameTeam), fisierIN);

        for (int j = 0; j<nrPlayers; j++) 
        {
            char line[100];
            fgets(line, sizeof(line), fisierIN);

            char* firstName = strtok(line, " ");
            char* lastName = strtok(NULL, " ");
            char* pointsStr = strtok(NULL, " ");
            
            int points = atoi(pointsStr);
        
        Player player;
            player.firstName = strdup(firstName);
            player.lastName = strdup(lastName);
            player.points = atoi(pointsStr);

        free(player.firstName);
        free(player.lastName);
        free(player.points);
        }

        fseek(fisierIN, 1, SEEK_CUR);
    }
   
    fclose(fisierIN);

    FILE *fisierOUT = fopen(output, "w");
    if(fisierOUT == NULL)
        {
            printf("Fisierul 'r.out' nu poate fi deschis.\n");
            return 1;
        }

    fclose(fisierOUT);

}
