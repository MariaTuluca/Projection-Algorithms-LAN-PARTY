#include<stdio.h>
#include<stdlib.h>

struct nod{
    int val;
    int height;
    struct nod* left, *right;
}; 
typedef struct nod Node;

 Node* search(Node* root, int key)
 {
    if (root == NULL || root->val == key)
    return root;

    if (root->val < key)
    return search(root->right, key);
    // daca valoarea din radacina e mai mare decat cheia
    return search(root->left, key);
 }


int nodeHeight (Node* root)
{
    if(root == NULL)
        return -1;
    else return root->height;
}

int max (int a,int b) {
    return ((a>b)?a:b);
}

Node * RightRotation ( Node *z) {
        // z nod cu —K— ¿1
    Node *y = z-> left ;
    Node *T3 = y-> right ;
    // Roteste
    y-> right = z;
    z-> left = T3;
    // Modifica inaltimile pentru z si y
    z-> height = max( nodeHeight (z-> left ) ,
    nodeHeight (z-> right ))+1;
    y-> height = max( nodeHeight (y-> left ) ,
    nodeHeight (y-> right ))+1;
    return y; // noua radacina
} 

Node * LeftRotation ( Node *z) {
    Node *y = z-> right ;
    Node *T2 = y-> left ;
    y-> left = z;
    z-> right = T2;
    z-> height = max( nodeHeight (z-> left ) ,
    nodeHeight (z-> right ))+1;
    y-> height = max( nodeHeight (y-> left ) ,
    nodeHeight (y-> right ))+1;
    return y;
}

Node * LRRotation ( Node *Z) {
    Z-> left = LeftRotation (Z-> left );
    return RightRotation (Z);
}

Node * RLRotation ( Node *Z) {
    Z-> right = RightRotation (Z-> right );
    return LeftRotation (Z);
}

Node * newNode ( int data ) {
    Node * node = ( Node *) malloc ( sizeof ( Node ));
    node -> val = data ;
    node -> left = node -> right = NULL ;
    return node ;
}

Node * insert ( Node * node , int key) {
// daca ( sub) arborele este gol , creaza nod
    if ( node == NULL ) return newNode ( key );
    // altfel , coboara la stanga sau dreapta
    if ( key < node -> val)
    node -> left = insert (node -> left , key );
    else if (key > node -> val)
    node -> right = insert (node ->right , key );
    // ! pointerul node se intoarce nemodificat pe acest return
    return node ;
}// !nu se adauga elemente egale

void preorder ( Node * root ) {
    if ( root ){
    printf ("%d ",root ->val );
    preorder (root -> left );
    preorder (root -> right );
    }
}

Node * insert_AVL( Node * node , int key) {
    if ( node == NULL ){
        node = ( Node *) malloc ( sizeof ( Node ));
        node ->val = key;
        node -> height = 0; // adaugare ca frunza
        node ->left = node -> right = NULL ;
        return node ;
    }
    
    if ( key < node -> val)
    node -> left = insert (node ->left , key );
    else if (key > node -> val)
    node -> right = insert (node ->right , key );
    else return node ; 

    node -> height = 1 + max( nodeHeight (node -> left ) ,nodeHeight (node -> right ));
    int k = ( nodeHeight (node ->left ) - nodeHeight (node -> right ));
    if (k > 1 && key < node -> left ->val)
    return RightRotation ( node );

    if (k < -1 && key > node -> right -> val)
    return LeftRotation ( node );

    if (k > 1 && key > node -> left -> val)
    return RLRotation ( node );

    if (k < -1 && key < node -> right ->val)
        return LRRotation ( node );
    return node ;
}

void anaf (Node* root, int *suma, int *nr){
    if(root->right != NULL)
        anaf(root->right, suma, nr);
    if(*suma != 0){
        *suma -= root->val;
       // printf(" %d ", *suma);
        *nr +=1; 
       // printf(" %d ", *nr);
    }
    if(*suma == 0)
        return;
    if(root->left != NULL)
        anaf(root->left, suma, nr);
}

int main()
{
    Node *root = NULL;
    int averi[9] = {30, 12, 10, 18, 28, 25, 23, 24, 40};
    //pt bts
    for(int i = 0; i<9; i++){
        root = insert(root, averi[i]);
    }
    preorder(root);
    printf("\n");

    Node *p = search(root, 28);
    Node *c = search(root, 25);
    p->left = LRRotation(c);    

    p = search(root, 18);
    c = search(root, 28);
    p->right = RightRotation(c);

    p = search(root, 12);
    c = search(root, 18);
    p->right = LeftRotation(c);

    p = search(root, 30);
    c = search(root, 12);
    p->left = LeftRotation(c);

    c = search(root, 30);
    root = RightRotation(c);

    preorder(root);

    int suma = 147;
    int nr = 0;
    anaf(root, &suma, &nr);

    printf("\n %d", nr);


    return 0;
}