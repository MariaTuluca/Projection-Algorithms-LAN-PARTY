#include "liste.h"
#include "functii-ajutatoare.h"
#include "cozi.h"

void primulTask(ListOfTeams **teamList, int *numberOfTeams, char *fileIn, char* fileOut)
{
    FILE *inputDate = fopen(fileIn, "rt");
    if(inputDate == NULL)
        {
            printf("Fisierul 'd.in' nu poate fi deschis.\n");
            return 1;
        }
    
    fscanf(inputDate, "%d", numberOfTeams);
    for(int j=0; j<*numberOfTeams; j++)
    {
        int nrPlayersOfTeam;
        Team *newTeam = NULL;
        ListOfPlayers *playerList = NULL;

        fscanf(inputDate, "%d", nrPlayersOfTeam);
        fgetc(inputDate);
        //citesc datele pentru players
        readTeamName(inputDate, &newTeam);
        readPlayers(inputDate, &playerList, nrPlayersOfTeam);
        fgetc(inputDate);
        
        addListOfPlayersToTeam(&newTeam, playerList);
        addTeamToTeamList(teamList, newTeam);
    }    

    fclose(inputDate);
    writeNamesOfTeams(*teamList, fileOut);
}

void alDoileaTask(ListOfTeams **teamList, int *numberOfTeams, char *fileOUT)
{
    //găsesc cea mai mare putere a lui doi mai mică decat numărul de echipe
    int powerOf2 = 0;
    while(pow(2, powerOf2) <= (*numberOfTeams))
    {
        powerOf2++;
    }

    //folosesc notația n pentru numărul dorit de echipe
    int n = pow(2, --powerOf2);
    for( ; n<(*numberOfTeams); (*numberOfTeams)--)
    {
        ListOfTeams *eliminatedTeam = NULL;

        findTeamForElimination(teamList, &eliminatedTeam);
        deleteTeam(teamList, eliminatedTeam);
    }

    writeNamesOfTeams(*teamList, fileOUT);
}  

int main(int argc, char* argv[])
{
    char *input = argv[1];

    FILE *file_tasks = fopen(input, "rt");
    if(file_tasks == NULL)
        {
            printf("Fisierul 'c.in' nu poate fi deschis.\n");
            return 1;
        }

    ListOfTeams *teamList = NULL;
    int numberOfTeams = 0;
    int tasks[5];
    
    for(int j=0; j<5; j++)
        fscanf(file_tasks, "%d", &tasks[j]);

    fclose(file_tasks);

    if(tasks[0] == 1)
            primulTask(&teamList, &numberOfTeams, argv[2], argv[3]);

     if(tasks[1] == 1)
            alDoileaTask(&teamList, &numberOfTeams, argv[3]);  

}
