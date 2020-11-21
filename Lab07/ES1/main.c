#include <stdio.h>
#include <stdlib.h>
typedef struct lato{
    int u, v;
}edge;
int check(int k, int sol[], int c[], int n, int e, edge l[]){
    int cont=0;
    for (int i = 0; i < n; ++i) {
        c[i]=0;
    }
    for (int i = 0; i < k; ++i)
        for (int j = 0; j < e; ++j)
            if (sol[i] == l[j].u || sol[i] == l[j].v) {
                if(c[j]!=1)
                    cont++;
                c[j]=1;
            }

    return cont>=e;
}
int vertexCover(int pos, edge *l, int e, int *sol, int n, int k, int start, int count, int *c){
    if(pos>=k){
        if(check(k, sol, c, n, e, l)==1){
            for (int i = 0; i < k; ++i) {
                printf("%d ", sol[i]);
            }
            printf("\n");
            return count +1;
        }
       return count;
    }
    for (int i=start; i<n; i++) {
        sol[pos] = i;
        count = vertexCover(pos+1, l, e, sol, n, k, i+1, count, c);
    }
    return count;
}
int main() {
    FILE *f;
    int n,e, cont=0;
    f=fopen("grafo.txt", "r+");
    fscanf(f,"%d %d", &n,&e);
    edge edges[n];
    for (int i = 0; i < e; ++i) {
        fscanf(f,"%d %d", &edges[i].u, &edges[i].v);
    }
    fclose(f);
    int *sol=calloc(n,sizeof(int));
    int *check=calloc(n,sizeof(int));
    for (int i = 0; i < n; ++i) {
        check[i]=0;
    }
    for (int k = 1; k <= n; ++k) {
        cont+=vertexCover(0, edges, e, sol, n, k, 0, 0,check);
    }
    printf("\n%d Trovati.", cont);
    return 0;
}
