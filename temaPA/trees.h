#include<stdlib.h>
#include "liste.h"

//funcții pentru arbori

//structură pentru binary search tree (BST)
typedef struct bstNode
{   Team *val;
    struct bstNode *left, *right;
}BSTNode;

BSTNode *BSTnewNode(Team *data);

void BST_insertion(BSTNode *bst_root, Team *team);

void createBST(BSTNode **root, ListOfTeams *the8Finalists);

void TeamToBeginningOfTeamList(ListOfTeams **BSTlist, Team *team);

void afișareBST(BSTNode *bst_root, ListOfTeams **BSTlist, char *fileOUT);

void deleteBST(BSTNode *bst_root);