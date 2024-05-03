#include<stdio.h>
#include<stdlib.h>

#define nrNod 8

typedef struct graph{
    int V;
    int E;
    int a[nrNod][nrNod];
}Graph;

void DFS_drumuri(Graph *g, int vizitat[], int index, int sursa, int dest, int drum[])
{
    int j;
    int nr_drumuri = 1;

    vizitat[sursa] = 1;
    drum[index++] = sursa;

    if(sursa == dest)
    {
        printf("Drumul %d de la 0 la 7: ", nr_drumuri);

        for(j = 0; j<index ; j++)
            printf("%d ->", drum[j]);

        printf("\n");
    }

    else
    {
        for(j = 0; j< g->V ; j++)
            if (!vizitat[j] && g->a[sursa][j] == 1)
                DFS_drumuri(g, vizitat, index, j, dest, drum);
    }

    vizitat[sursa] = 0;
    nr_drumuri++;
}

int main()
{
    Graph *g = (Graph*)malloc(sizeof(Graph));

    int V = nrNod;
    g->V = V;

    for(int i=0; i<V; i++)
        for(int j=0; j<V; j++)
            g->a[i][j] = 0;

    int x=1, y=1;

    printf("Introdu perechi de vecini pt graful orientat(-1 -1 pentru a te opri):\n");
    while(x!=-1 && y!=-1)
    {
      scanf("%d %d", &x, &y);
      g->a[x][y] = 1;
    }

    g->E = 0;

    for(int i=0; i<V; i++)
        for(int j=0; j<V; j++)
           if(g->a[i][j] == 1) g->E++;

   int vizitat[8] = {0};
   int drum[nrNod], index = 0;

   DFS_drumuri(g, vizitat, index, 0, 7, drum);

}
