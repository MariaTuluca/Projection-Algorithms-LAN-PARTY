#include"dendogram.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	Node *root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);
	return 0;
}

