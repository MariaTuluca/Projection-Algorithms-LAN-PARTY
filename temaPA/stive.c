#include "stive.h"
#include "cozi.h"
#include "functii-ajutatoare.h"

//fișier cu funcții pentru stive

Team *top(StackNode *top)
{
	return top->subject;
}

int isStackEmpty(StackNode *top)
{
	return top==NULL;
}

void deleteStack(StackNode **top)
{
	StackNode *temp;
	while ((*top)!=NULL){ 
		temp=*top;
		*top=(*top)->next;
		free(temp);
	}
}

Team *pop(StackNode **top) 
{
    StackNode *temp = (*top);
	Team *aux = temp->subject;

	*top=(*top)->next;
	free(temp);
	return aux;
}

void push(StackNode **top, Team *v) 
{
	StackNode* newNode = malloc(sizeof(StackNode));
	if(newNode == NULL)
	{
		printf("Eroare alocare memorie pentru newNode stack.\n");
		return;
	}

	newNode->subject = v;
	newNode->next=*top;
	*top=newNode;
}

//funcție pentru creare stive de winners și de losers
void winnersAndLosersStacks(StackNode **winners, StackNode **losers, Queue *matches)
{
	Team *teamWin = NULL;
    Team *teamLose = NULL;

	while(!isQueueEmpty(matches))
	{//prelucrez primul meci din coadă
		Match *aux_match = deQueue(matches);
		float avgTeam1 = ScoreOfTeam(aux_match->team_1), avgTeam2 = ScoreOfTeam(aux_match->team_2);

		if(avgTeam2 <= avgTeam1) 	//câștigă prima echipă
		{teamWin = aux_match->team_1;
		 teamLose = aux_match->team_2;
		}
		else  //câștigă a doua echipă
		{teamLose = aux_match->team_1;
		 teamWin = aux_match->team_2;
		}	

		push(winners, teamWin);
		push(losers, teamLose);

		free(aux_match);
	}
}

//funcție pentru adăugare puncte la jucătorii care au câștigat
void onePointToEveryWinnerPlayer(StackNode *winners)
{
	while(!isStackEmpty(winners))
	{
		ListOfPlayers *aux = winners->subject->players;
		while(aux != NULL)
		{//adaug punctul fiecărui jucător
			aux->player->points = aux->player->points + 1;
			aux = aux->next;
		}
		//trec la următoarea echipă
		winners = winners->next;
	}
}


//funcție pentru afișare meci în fișier, cu regulile din cerință
void writeTheMatchFormated(Match *match, char *fileOUT)
{
    FILE *fout;
    if((fout = fopen(fileOUT, "at")) != NULL)
        fprintf(fout, "%-33s-%33s\n", match->team_1->name, match->team_2->name);

    fclose(fout);
}

//funcție pentru afișare număr rundă în fișier, cu regulile din cerință 
void writeWinnersTitleFormated(int numberOfRounds, char *fileOUT)
{
    FILE *f;
    if((f = fopen(fileOUT, "wt")) != NULL)
        fprintf(f, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
    else printf("Nu a putut fi deschis fișierul pentru printare număr round!");

    fclose(f);
}

//funcție pentru afișare echipe câștigătoare în fișier, cu regulile din cerință
void writeWinnersFormated(StackNode *winners, char *fileOUT)
{
	FILE *fout;
	if((fout = fopen(fileOUT, "wt")) != NULL)
	{
		while(winners != NULL)
		{
			float score = ScoreOfTeam(winners->subject);
			fprintf(fout, "%-34s-  %.2f\n", winners->subject->name, score);
			winners = winners->next;
		}
	}
	else printf("Nu a putut fi deschis fișierul pentru printare detalii echipă câștigătoare!");

	fclose(fout);
}

