#include <stdlib.h>
#include <stdio.h>
#include<string.h>

typedef struct N{
	char obj;
	struct  N  *left,*right;
}Node;


Node* createNode(char obj);

Node* createTree(Node *root);

int height(Node* root);

void printLevel(Node* root, int level);

void levelOrderTraversal(Node* root);


