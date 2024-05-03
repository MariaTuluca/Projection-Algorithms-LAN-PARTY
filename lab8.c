#include<stdio.h>
#include<stdlib.h>

typedef int Data;

typedef struct N{
    Data val;
    struct N *left, *right;
}Node;

Node* newNode(Data data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = data ;
    node->left = node->right = NULL ;
    return node;
}

Node* insert(Node* node, int key)
{
    if (node == NULL) return newNode(key);

    if (key < node->val)
        node->left = insert(node->left, key);
    else if (key > node->val)
        node->right = insert(node->right, key);

    return node;
}

void preorder(Node* root)
{
    if (root){
    printf("%d ",root->val );
    preorder(root->left);
    preorder(root->right);
    }
}
/*
int nodeHeight(Node* root )
{
    if (root==NULL) return -1;
    else return root->height ;
}
Node* RightRotation(Node *z)
{
    Node *y = z->left ;
    Node *T3 = y->right ;

    y->right = z;
    z->left = T3;
    z->height = max(nodeHeight(z->left),nodeHeight(z->right))+1;
    y->height = max(nodeHeight(y->left),nodeHeight(y->right))+1;

    return y;
}

Node* LeftRotation(Node *z)
{
    Node *y = z->right;
    Node *T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeight(z->left),nodeHeight(z->right))+1;
    y->height = max(nodeHeight(y->left),nodeHeight(y->right))+1;

    return y;
}


Node* LRRotation(Node *Z)
{
    Z->left = leftRotation(Z->left);
    return rightRotation(Z);

}

Node* RLRotation(Node *Z)
{
    Z->right = rightRotation(Z->right);
    return leftRotation(Z);
}
*/

int main()
{
    Node *root = NULL;
    int averi[]={30, 12, 10, 18, 28, 25, 23, 24, 40};

    for(int i = 0; i<9; i++)
    {
        root = insert(root, averi[i]);
    }
    preorder(root);

    printf("\n");

    Node *p = search(root,28);
    Node *c = search(root,25);
    p->left = leftRotation(c);

}
