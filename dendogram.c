#include "dendogram.h"
#include <stdlib.h>
#include <stdio.h>


Node* createNode(char obj){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->obj = obj;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* createTree(Node *root){
	root = createNode('9');
	root->left = createNode('8');
	root->right = createNode('6');
	root->left->left = createNode('4');
	root->left->right = createNode('7');
	root->right->left = createNode('3');
	root->right->right = createNode('K');
	root->left->left->left = createNode('0');
	root->left->left->right = createNode('1');
	root->left->right->left = createNode('5');
	root->left->right->right = createNode('H');
	root->right->left->left = createNode('I');
	root->right->left->right = createNode('J');
	root->left->left->left->left = createNode('A');
	root->left->left->left->right = createNode('B');
	root->left->left->right->left = createNode('C');
	root->left->left->right->right = createNode('D');
	root->left->right->left->left = createNode('2');
	root->left->right->left->right = createNode('G');
	root->left->right->left->left->left = createNode('E');
	root->left->right->left->left->right = createNode('F');

	return root;
}

int height(Node*root){
	int hs, hd;
	if (root==NULL) return -1;
	hs = height(root->left);
	hd = height(root->right);
	return 1+((hs>hd) ? hs:hd);
}

void printLevel(Node* root, int level){
	if (root == NULL)   return;
	if (level == 0) printf("%c ", root->obj);
	else if (level > 0) {
		printLevel(root->left, level-1);
		printLevel(root->right, level-1);
	}
}

void levelOrderTraversal(Node* root){
	int h = height(root);
	int i;
	for (i=0; i<=h; i++){
		printLevel(root, i);
		printf("\n");
	}
	return;
}
