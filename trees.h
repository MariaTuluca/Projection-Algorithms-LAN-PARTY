#include<stdlib.h>
#include<string.h>
#include "liste.h"
#include "functii-ajutatoare.h"

//funcții create și luate din curs pentru arbori
#ifndef TREES_H
#define TREES_H
//structură pentru binary search tree (BST)
typedef struct bstNode
{   
    Team *val;
    struct bstNode *left, *right;
}BSTNode;

//structură pentru arbore AVL
typedef struct AVLNode
{
    int height;
    Team *val;
    struct AVLNode *left, *right;
}AVLNode;

#endif

BSTNode *BSTnewNode(Team *data);

BSTNode *BST_insertion(BSTNode *bst_root, Team *team);

void createBST(BSTNode **root, ListOfTeams *the8Finalists);

void TeamToTeamList(ListOfTeams **BSTlist, Team *team);

void afisareBST(BSTNode *bst_root, ListOfTeams **BSTlist, FILE *fileOUT);

void deleteBST(BSTNode *bst_root);

int nodeHeight(AVLNode *node);

AVLNode *RightRotation(AVLNode *z);

AVLNode *LeftRotation(AVLNode *z);

AVLNode *RLRotation(AVLNode *z);

AVLNode *LRRotation(AVLNode *z);

void whichRotation(AVLNode **node, Team *team, float scoreTeam, float scoreLeftChild, float scoreRightChild, int k);

AVLNode *AVL_insertion(Team *team, AVLNode *node);

void AVL_DRSbrowse(AVLNode *root, FILE* fileOUT, int lvl);

void deleteAVL(AVLNode *AVL_root);

