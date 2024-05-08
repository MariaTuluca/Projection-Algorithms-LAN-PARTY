#include "liste.h"
#include "functii-ajutatoare.h"
#include "cozi.h"
#include "stive.h"
#include "trees.h"

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
    { powerOf2++;
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

void alTreileaTask(ListOfTeams **teamList, ListOfTeams **the8Finalists, char *fileOUT)
{   //creez o coadă cu meciuri
    Queue *matches = NULL;
    populateQueue(&matches, *teamList);
    //creez stiva pentru învingători
    StackNode *winners = NULL;
    int numberOfRounds = 0, numberOfTeams;

    while(numberOfTeams > 1)
    {   numberOfRounds++;
        //scriem în fișier numele rundei și a echipelor, după regula de afișare din cerință 
        FILE *fout;
        if((fout = fopen(fileOUT, "at") == NULL))
            printf("Eroare la deschiderea fișierului de printare runde.");
        else{
            fprintf(fout, "\n--- ROUND NO:%d\n", numberOfRounds);
            
            QueueNode *aux = matches->front;
            while(aux != NULL)
            {
              writeTheMatchFormated(aux->subject, fileOUT);
              aux = aux->next;
            }
            fclose(fout);
        }

        StackNode *losers = NULL; //creez stiva pentru învinși

        winnersAndLosersStacks(&winners, &losers, matches);
        onePointToEveryWinnerPlayer(winners);
        writeWinnersTeamFormated(numberOfRounds, fileOUT); //scriu toate datele în fișier
        writeWinnersFormated(winners, fileOUT);
        deleteStack(losers);
        //creez iar meciuri cu echipe care au câștigat
        remakeQueueOfMatches(matches, winners, &numberOfTeams);
        //dacă am ajuns la cei 8 finaliști, îi stocăm în lista finaliștilor 
        if(numberOfTeams == 8)
            listOfThe8Finalists(matches->front,the8Finalists);
    }
    //eliberez spațiul folosit de stiva de câștigători și coada de meciuri
    deleteQueue(matches);
    deleteStack(&winners);
}

void alPatruleaTask(ListOfTeams *the8Finalists, ListOfTeams **the8FinalistsInDescendingOrder, char *fileOUT)
{//inițializez bst-ul și îl creez
    BSTNode *bst_root = NULL;
    createBST(&bst_root, the8Finalists);

    //afișăm în ordine descrescătoare clasamentul cu ajutorul arborelui
    FILE *fout;
    if((fout = fopen(fileOUT, "wt") == NULL))
    {    fprintf(fout, "\nTOP 8 TEAMS:\n");
            fclose(fout);
    }
    afișareBST(bst_root, the8FinalistsInDescendingOrder, fileOUT);
    //eliberăm memoria ocupată de bst
    deleteBST(bst_root);
}

//funcția main cu apelurile către fiecare task
int main(int argc, char* argv[])
{
    char *input = argv[1];

    FILE *file_tasks = fopen(input, "rt");
    if(file_tasks == NULL)
        {   printf("Fisierul 'c.in' nu poate fi deschis.\n");
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
 
    ListOfTeams *the8Finalists = NULL;
    if(tasks[2] == 1)
            alTreileaTask(&teamList, &the8Finalists, argv[3]);

    freeListOfTeams(&teamList);

    ListOfTeams *the8FinalistsInDescendingOrder = NULL;
    if(tasks[3] == 1)
            alPatruleaTask(the8Finalists, &the8FinalistsInDescendingOrder, argv[3]);

    return 0;
}
