#include <stdio.h>
#define MAXR 50
int leggiMat(int maxN, int* nr,int * nc,int mat[maxN][maxN]){
    FILE *f;
    f=fopen("mappa.txt","r");
    if(f==NULL) {
        printf("apertura file non avvenuta");
        return 1;
    }
    fscanf(f, "%d %d", nr, nc);
    if(*nr > maxN || *nc > maxN)
        return 1;
    for (int i = 0; i < *nr; ++i) {
        for (int j = 0; j < *nc; ++j) {
            fscanf(f,"%d",&mat[i][j]);
        }
    }
    fclose(f);
    return 0;
}
int riconosciRegione(int mat[MAXR][MAXR], int nr, int nc, int ir, int ic, int *b, int *h){
    if(mat[ir][ic] != 1 || (ir > 0 && mat[ir-1][ic]) || (ic > 0 && mat[ir][ic-1])){
        *b =0;
        *h =0;
        return 0;
    }
    int i;
    for(i = ic; i < nc && mat[ir][i] == 1; i++);
    *b = i-ic;
    for( i = ir; i < nr && mat[i][ic] == 1; i++);
    *h = i-ir;

    return 1;
}
int main() {
    int b,h,x,y;
    int nr=0,nc=0;
    int mat[MAXR][MAXR];
    leggiMat(MAXR,&nr,&nc,mat);
    do {
        printf("Inserisci le coordinate nel formato x,y e valori >=0: ");
        scanf("%d,%d",&x, &y);
    }while(x<0 || y <0 || x > nr || y > nc);

    printf("\nTrovato: %d",riconosciRegione(mat,nr,nc, x,y, &b, &h));
}
