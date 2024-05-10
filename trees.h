#include<stdlib.h>
#include<string.h>
#include "liste.h"

//funcții create și luate din curs pentru arbori

//structură pentru binary search tree (BST)
typedef struct bstNode
{   Team *val;
    struct bstNode *left, *right;
}BSTNode;

//structură pentru arbore AVL
typedef struct avlNode
{
    int height;
    Team *val;
    struct avlNnode;
}AVLNode;

BSTNode *BSTnewNode(Team *data);

void BST_insertion(BSTNode *bst_root, Team *team);

void createBST(BSTNode **root, ListOfTeams *the8Finalists);

void TeamToTeamList(ListOfTeams **BSTlist, Team *team);

void afișareBST(BSTNode *bst_root, ListOfTeams **BSTlist, char *fileOUT);

void deleteBST(BSTNode *bst_root);

int nodeHeight(AVLNode *node);

AVLNode *RightRotation(AVLNode *z);

AVLNode *LeftRotation(AVLNode *z);

AVLNode *RLRotation(AVLNode *z);

AVLNode *LRRotation(AVLNode *z);

void whichRotation(AVLNode **node, Team *team, float scoreTeam, float scoreLeftChild, float scoreRightChild, int k);

AVLNode *AVL_insertion(Team *team, AVLNode *node);

void AVL_DRSbrowse(AVLNode *root, char* fileOUT, int lvl);

void deleteAVL(AVLNode *AVL_root);

