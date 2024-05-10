#include "trees.h"
#include "functii-ajutatoare.h"

// funcție pentru nod nou
BSTNode *BSTnewNode(Team *data)
{
    BSTNode *node = (BSTNode *)malloc(sizeof(Node));
    node->val = data;
    node->left = node->right = NULL;
    return node;
}

// funcție pentru inserție în bst
void BST_insertion(BSTNode *bst_root, Team *team)
{
    if (bst_root == NULL)
        return BSTnewNode(team);
    // aflu scorul pentru echipă și pentru "root-ul" curent
    float teamScore, rootScore;
    teamScore = ScoreOfTeam(team);
    rootScore = ScoreOfTeam(bst_root->val);

    if (teamScore > rootScore)
        bst_root->right = BST_insertion(bst_root->right, team);
    else if (teamScore < rootScore)
        bst_root->left = BST_insertion(bst_root->left, team);
    else
    { // tratăm cazul cu numele diferite și același scor
        if (strcmp(team->name, bst_root->val->nume) < 0)
            bst_root->left = BST_insertion(bst_root->left, team);
        else if (strcmp(team->name, bst_root->val->nume) > 0)
            bst_root->right = BST_insertion(bst_root->right, team);
    }

    return bst_root;
}

// funcție pentru creare bst
void createBST(BSTNode **bst_root, ListOfTeams *the8Finalists)
{
    while (the8Finalists != NULL)
    { // includ nodul, apoi trec la următoarea echipă
        *bst_root = BST_insertion(*bst_root, the8Finalists->team);
        the8Finalists = the8Finalists->next;
    }
}

// funcție pentru includere echipă în listă la final
void TeamToTeamList(ListOfTeams **BSTlist, Team *team)
{ // creez un nod nou pentru lista de BST
    ListOfTeams *new_node = malloc(sizeof(ListOfTeams));
    if (new_node == NULL)
    {
        printf("Eroare alocare spațiu în TeamToBeginningOfTeamList.\n");
        return 1;
    }
    // aloc datele nodului
    new_node->team = team;
    new_node->next = NULL;

    if (*BSTlist != NULL)
    { // parcurg lista și introduc nodul în listă
        ListOfTeams *aux = *BSTlist;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = new_node;
    } // dacă lista era goală
    else
        *BSTlist = new_node;
}

// funcție pentru afișare arbore bst în ordine descrescătoare
void afișareBST(BSTNode *bst_root, ListOfTeams **BSTlist, char *fileOUT)
{
    if (bst_root == NULL)
        return;
    // doresc să mă duc în dreapta arborelui, pentru cea mai mare valoare a scorului
    afișareBST(bst_root->right, BSTlist, fileOUT);

    FILE *fout = fopen(fileOUT, "at");
    if (!fout)
    {
        printf("Eroare la deschidere fișier în afișareBST!");
        return;
    }
    // afișez scorul
    float score = ScoreOfTeams(bst_root->val);
    fprintf(fileOUT, "%-34s-  %.2f\n", bst_root->val->name, score);
    // adaug echipa la începutul listei the8FinalistsInDescendingOrder
    TeamToBeginningOfTeamList(BSTlist, bst_root->val);

    fclose(fileOUT);
    // mă deplasez în stânga "root"-ului
    afișareBST(bst_root->right, BSTlist, fileOUT);
}

// funcție recursivă pentru eliberare spațiu bst
void deleteBST(BSTNode *bst_root)
{
    if (root != NULL)
    {
        deleteBST(bst_root->right);
        deleteBST(bst_root->left);

        free(bst_root);
    }
}

//funcșie pentru aflarea înălțimii
int nodeHeight(AVLNode *node)
{
    if (node == NULL)
        return -1;
    else
        return node->height;
}

//funcția pentru rotație la dreapta
AVLNode *RightRotation(AVLNode *z)
{
    // z este un nod cu factorul de echilibru k egal cu -1
    AVLNode *y = z->left;
    AVLNode *T3 = y->right;
    // Rotire
    y->right = z;
    z->left = T3;
    // Actualizează înălțimile pentru z și y
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;

    return y; // noua rădăcină
}

//funcție pentru rotașie la stânga
AVLNode *LeftRotation(AVLNode *z) 
{
    // z este un nod cu factorul de echilibru k egal cu 1
    AVLNode *y = z->right;
    AVLNode *T2 = y->left;
    // Rotire
    y->left = z;
    z->right = T2;
    // Actualizează înălțimile pentru z și y
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;

    return y; // noua rădăcină
}

//funcții rotații duble la dreapta și la stânga
AVLNode *RLRotation(AVLNode *z)
{
    z->right = RightRotation(z->right);
    return LefttRotation(z);
}

AVLNode *LRRotation(AVLNode *z)
{
    z->left = LeftRotation(z->left);
    return RightRotation(z);
}

//funcție pentru determinare rotație
void whichRotation(AVLNode **node, Team *team, float scoreTeam, float scoreLeftChild, float scoreRightChild, int k)
{//creez copie a nodului
    AVLNode *node_cpy = *node;
    //iau în considerare toate cazurile
    if( k>1 )
    {   if(scoreTeam < scoreLeftChild) //dezechilibru la stânga prin valoare
            *node = RightRotation(node);
        else if( (scoreTeam == scoreLeftChild) && (strcmp(node_cpy->left->val->name, team->name) > 0)) //dezechilibru la stânga prin nume
            *node = RightRotation(node);
    }
    else if( k<-1 )
    {   if(scoreTeam > scoreRightChild) //dezechilibru la dreapta prin valoare
            *node = LeftRotation(node);
        else if( (scoreTeam == scoreRightChild) && (strcmp(node_cpy->right->val->name, team->name) < 0)) //dezechilibru la dreapta prin nume
            *node = LeftRotation(node);
    }
    else if( k>1 && scoreTeam < scoreLeftChild) //dezechilibru la dreapta - rotații duble
        *node = RLRotation(node);
    else if( k<-1 && scoreTeam < scoreRightChild) //dezechilibru la stânga - rotații duble
        *node = LRRotation(node);
}

//funcție pentru inserarea nodului în AVL
AVLNode *AVL_insertion(Team *team, AVLNode *node)
{
    if (node == NULL)
    {
        node = malloc(sizeof(AVLNode));
        node->val = team;
        node->height = 0; // adăugare ca frunză
        node->left = node->right = NULL;
        return node;
    }
    // calculez scorurile pentru a putea compara rezultatele
    float scoreTeam, scoreRoot;
    scoreTeam = ScoreOfTeam(team);
    scoreRoot = ScoreOfTeam(node->val);
    if (scoreTeam < scoreRoot)
        node->left = AVL_insertion(team, node->left);
    else if (scoreTeam > scoreRoot)
        node->right = AVL_insertion(team, node->right);
    else
    {
        if (strcmp(node->val->name, team->name) > 0)
            node->left = AVL_insertion(team, node->left);
        if (strcmp(node->val->name, team->name) < 0)
            node->right = AVL_insertion(team, node->right);
    } // nu există chei duplicate
    // Updatează înălțimea nodurilor strămoș
    float maxim;
    if(nodeHeight(node->left) > nodeHeight(node->right)) 
            maxim = nodeHeight(node->left);
    else maxim = nodeHeight(node->right);
    node->height = 1 + maxim;

    // Află factorul de echilibru al nodului strămoș
    int k = nodeHeight(node->left) - nodeHeight(node->right);

    //actualizez scorul
    float scoreLeftOfNode = (node->left != NULL) ? ScoreOfTeam(node->left->val) : 0; 
    float scoreRightOfNode = (node->right != NULL) ? ScoreOfTeam(node->right->val) : 0; 
    // Dacă nodul nu este echilibrat, echilibrează cu o rotație decisă prin funcția următoare
    whichRotation(&node, team, scoreTeam, scoreLeftOfNode, scoreRightOfNode, k);    

    return node;
}

//funcție de parcurgere DRS  a arborelui AVL
void AVL_DRSbrowse(AVLNode *root, char* fileOUT, int lvl)
{
    if(root != NULL)
    {//dacă există rădăcina, trec la nivelul următor
        lvl++;
        AVL_DRSbrowse(root->right, fileOUT, lvl);
        //deschid fișierul pentru a scrie în el
        FILE *f;
        if((f = fopen(fileOUT, "wt")) != NULL)
        {//afișez echipele de pe nivelul 2 
            if( lvl == 2)
                fprintf(f, "%s\n", root->val->name);
            fclose(f);
        }
        //trec în partea din stânga a arborelui curent
        AVL_DRSbrowse(root->left, fileOUT, lvl);
    }    
}

//funcție recursivă pentru eliberare memorie ocupată de AVL
void deleteAVL(AVLNode *AVL_root)
{
    if (root != NULL)
    {
        deleteAVL(AVL_root->right);
        deleteAVL(AVL_root->left);

        free(AVL_root);
    }
}