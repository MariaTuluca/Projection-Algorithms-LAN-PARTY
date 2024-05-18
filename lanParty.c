#include<math.h>
#include "liste.h"
#include "functii-ajutatoare.h"
#include "cozi.h"
#include "stive.h"
#include "trees.h"

void primulTask(ListOfTeams **teamList, int *numberOfTeams, char *fileIn, FILE* fileOut)
{
    FILE *inputDate = fopen(fileIn, "rt");
    if(inputDate == NULL)
    {   printf("Eroare la deschidere d.in.");
        exit(1);
    }

    fscanf(inputDate, "%d", numberOfTeams);
    
    for(int j=0; j< *numberOfTeams; j++)
    {
        Team *newTeam = NULL;
        ListOfPlayers *playerList = NULL;
        //citesc datele pentru team și players
        readDate(inputDate, &newTeam, &playerList);
        //adaug lista de players la team și echipa la lista de echipe
        addListOfPlayersToTeam(&newTeam, playerList);
        addTeamToBegTeamList(teamList, newTeam);
    }    
    fclose(inputDate);

    writeNamesOfTeams(*teamList, fileOut);
}

void alDoileaTask(ListOfTeams **teamList, int *numberOfTeams, FILE *fileOUT)
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

void alTreileaTask(ListOfTeams **teamList, ListOfTeams **the8Finalists, FILE *fileOUT)
{   //creez o coadă cu meciuri
    Queue *matches = NULL;
    populateQueue(&matches, *teamList);

    StackNode *winners = NULL;  //creez stiva pentru învingători
    int numberOfRounds = 0, numberOfTeams;

    while(numberOfTeams > 1)
    {   numberOfRounds++;
        //scriem în fișier numele rundei și a echipelor, după regula de afișare din cerință 
    
        fprintf(fileOUT, "\n--- ROUND NO:%d\n", numberOfRounds);
            
        QueueNode *aux = matches->front;
        while(aux != NULL)
        {
            fprintf(fileOUT, "%-33s-%33s\n", aux->subject->team_1->name, aux->subject->team_2->name);
            aux = aux->next;
        }
        
        StackNode *losers = NULL; //creez stiva pentru învinși
        winnersAndLosersStacks(&winners, &losers, matches);

        while(!isStackEmpty(winners))
	    {   ListOfPlayers *aux = winners->subject->players;
		    if(aux != NULL)     //adaug mereu punctul primului jucător din fiecare echipă, pentru că nu mă interesează punctajul individual al jucătorilor
		        aux->player->points = aux->player->points + 1;

		    winners = winners->next;    //trec la următoarea echipă
	    }

        fprintf(fileOUT, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
        writeWinnersFormated(winners, fileOUT);
        deleteStack(&losers);
        //creez iar meciuri cu echipe care au câștigat
        remakeQueueOfMatches(matches, &winners, &numberOfTeams);
        //dacă am ajuns la cei 8 finaliști, îi stocăm în lista finaliștilor 
        if(numberOfTeams == 8)
            listOfThe8Finalists(matches->front, the8Finalists);
    }
    //eliberez spațiul folosit de stiva de câștigători și coada de meciuri
    deleteQueue(matches);
    deleteStack(&winners);
}

void alPatruleaTask(ListOfTeams *the8Finalists, ListOfTeams **the8FinalistsInDescendingOrder, FILE *fileOUT)
{//inițializez bst-ul și îl creez în ordine descrescătoare
    BSTNode *bst_root = NULL;
    createBST(&bst_root, the8Finalists);

    //afișăm în ordine descrescătoare clasamentul cu ajutorul arborelui
    fprintf(fileOUT, "\nTOP 8 TEAMS:\n");
    afisareBST(bst_root, the8FinalistsInDescendingOrder, fileOUT);
    //eliberez memoria ocupată de bst ul 
    deleteBST(bst_root);
}

void alCincileaTask(ListOfTeams *the8FinalistsInDescendingOrder, FILE *fileOUT)
{//inițializez arborele AVL
    AVLNode *AVL_root = NULL;

    while(the8FinalistsInDescendingOrder != NULL)
    {//introduc echipa în acesta
        AVL_root = AVL_insertion(the8FinalistsInDescendingOrder->team, AVL_root);
    //trec la următoarea
        the8FinalistsInDescendingOrder = the8FinalistsInDescendingOrder->next;
    }
    //scriu în fișier cu forma cerută
    fprintf(fileOUT, "\nTHE LEVEL 2 TEAMS ARE:\n");
    //inițiez o parcurgere DRS pentru afișare în ordine descrescătoare a scorurilor
    int lvl = -1;
    AVL_DRSbrowse(AVL_root, fileOUT, lvl);
    //eliberez memoria ocupată de AVL
    deleteAVL(AVL_root);
}

//funcția main cu apelurile către fiecare task
int main(int argc, char* argv[])
{
    FILE *inputC = fopen(argv[1], "rt");
    if(inputC == NULL)
        {   printf("Fisierul 'c.in' nu poate fi deschis.\n");
            return 0;
        }
    //mă folosesc de citire pentru a verifica dacă pot face fiecare task
    int tasks[5] = {0};
    for(int j=0; j<5; j++)
    {   int i;
        fscanf(inputC, "%d", &i);
        fscanf(inputC, " ");
        tasks[j] += i;
    }
    fclose(inputC);

    //pregătesc fișierele de date și de ieșire
    char *inputD = (char*)malloc(15*sizeof(char));
    strcpy(inputD, argv[3]);

    char *OUTPUT = (char*)malloc(15*sizeof(char));
    strcpy(OUTPUT, argv[3]);

    ListOfTeams *teamList = NULL;
    int numberOfTeams = 0;

    FILE *output = fopen(OUTPUT, "wt");
    if(output == NULL)
    {   printf("Probleme la deschidere fisier de afișare nume echipe!");
        exit(1);
    }

    if(tasks[0] != 0)
            primulTask(&teamList, &numberOfTeams, inputD, output);

    if(tasks[1] != 0)
            alDoileaTask(&teamList, &numberOfTeams, output);  
 
    ListOfTeams *the8Finalists = NULL;
    if(tasks[2] != 0)
            alTreileaTask(&teamList, &the8Finalists, output);
    freeListOfTeams(&teamList);

    ListOfTeams *the8FinalistsInDescendingOrder = NULL;
    if(tasks[3] != 0)
            alPatruleaTask(the8Finalists, &the8FinalistsInDescendingOrder, output);

    if (tasks[4] != 0)
            alCincileaTask(the8FinalistsInDescendingOrder, output);
    freeListOfTeams(&the8FinalistsInDescendingOrder);

    fclose(output);
    return 0;
}
