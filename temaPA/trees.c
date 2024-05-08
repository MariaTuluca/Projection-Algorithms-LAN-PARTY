#include "trees.h"
#include "functii-ajutatoare.h"

//funcție pentru nod nou
BSTNode *BSTnewNode(Team *data)
{
    BSTNode *node = (BSTNode*)malloc(sizeof(Node));
    node->val = data;
    node->left = node->right = NULL;
    return node;
}

//funcție pentru inserție în bst
void BST_insertion(BSTNode *bst_root, Team *team)
{
    if(bst_root == NULL) return BSTnewNode(team);
    //aflu scorul pentru echipă și pentru "root-ul" curent
    float teamScore, rootScore;
    teamScore = ScoreOfTeam(team);
    rootScore = ScoreOfTeam(bst_root->val);

    if(teamScore > rootScore)
        bst_root->right = BST_insertion(bst_root->right, team);
    else if(teamScore < rootScore)
        bst_root->left = BST_insertion(bst_root->left, team);
    else{//tratăm cazul cu numele diferite și același scor
        if(strcmp(team->name, bst_root->val->nume) < 0)
            bst_root->left = BST_insertion(bst_root->left, team);
        else if(strcmp(team->name, bst_root->val->nume) > 0)
            bst_root->right = BST_insertion(bst_root->right, team);
    }

    return bst_root;
}

//funcție pentru creare bst
void createBST(BSTNode **bst_root, ListOfTeams *the8Finalists)
{
    while(the8Finalists != NULL)
    {//includ nodul, apoi trec la următoarea echipă
        *bst_root = BST_insertion(*bst_root, the8Finalists->team);
        the8Finalists = the8Finalists->next;
    }
}

//funcție pentru includere echipă în listă la final
void TeamToTeamList(ListOfTeams **BSTlist, Team *team)
{//creez un nod nou pentru lista de BST 
    ListOfTeams *new_node = malloc(sizeof(ListOfTeams));
    if(new_node == NULL)
        {
            printf("Eroare alocare spațiu în TeamToBeginningOfTeamList.\n");
            return 1;
        }
    //aloc datele nodului
    new_node->team = team;
    new_node->next = NULL;

    if(*BSTlist != NULL)
    {//parcurg lista și introduc nodul în listă
        ListOfTeams *aux = *BSTlist;
        while(aux->next != NULL)
        {
            aux = aux->next;
        } 
        aux->next = new_node;
    }//dacă lista era goală
    else *BSTlist = new_node;
}

//funcție pentru afișare arbore bst în ordine descrescătoare
void afișareBST(BSTNode *bst_root, ListOfTeams **BSTlist, char *fileOUT)
{
    if(bst_root == NULL)
        return;
    //doresc să mă duc în dreapta arborelui, pentru cea mai mare valoare a scorului
    afișareBST(bst_root->right, BSTlist, fileOUT);

    FILE *fout = fopen(fileOUT, "at");
    if(!fout)
    {   printf("Eroare la deschidere fișier în afișareBST!");
        return;
    }
    //afișez scorul
    float score = ScoreOfTeams(bst_root->val);
    fprintf(fileOUT, "%-34s-  %.2f\n", bst_root->val->name, score);
    //adaug echipa la începutul listei the8FinalistsInDescendingOrder
    TeamToBeginningOfTeamList(BSTlist, bst_root->val);

    fclose(fileOUT);  
    //mă deplasez în stânga "root"-ului
    afișareBST(bst_root->right, BSTlist, fileOUT);
}

//funcție recursivă pentru eliberare spațiu bst
void deleteBST(BSTNode *bst_root)
{
    if(root != NULL)
    {
        deleteBST(bst_root->right);
        deleteBST(bst_root->left);

        free(bst_root);
    }
}