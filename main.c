#include"dendogram.h"

int FindPath(Node *root, int path[], char key, int* lung)
{
    if(root == NULL)
            return 0;

    if(root->obj == key)
            return 1;

    path[(*lung)++] = root->obj - '0';

    if(FindPath(root->left, path, key, lung) || FindPath(root->right, path, key, lung))
        return 1;

    (*lung)--;

    return 0;
}

int main()
{
	Node *root = NULL;
	root = createTree(root);
	levelOrderTraversal(root);

    printf("\n");

	char c = 'A';
	int path[15];

//	int mat[10][10];

    for( ; c <='K'; c++)
    {
        int dim = 0;
//        int nr = 0;

        printf("%c: ", c);
        FindPath(root, path, c, &dim);
//        mat[nr++][] = path[];

        for(int i = 0; i<dim; i++)
        {
            printf("%d ", path[i]);
        }

        printf("\n");

    }

//intr-o functie
/*    for(int nr = 0; nr<10; nr++)
    {
        printf("%d: ", i);

       for(int i = 0; i<10; i++)
       {
           car = 'A';

           for(int j = 0; j<10, car++; j++)
            if(mat[i][j] == nr) printf(" %c ", car);

            printf("\n");

       }

    }
 */

}

