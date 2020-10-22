#include <stdio.h>

#define maxN 50
typedef struct{
    int x,y,b,h,a,val;
}dim;

int leggiMat(FILE *fin,int nr,int nc,int mat[nr][nc]){

    if(nr > maxN || nc > maxN)
        return 1;
    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j)
            fscanf(fin, "%d ",&mat[i][j]);
    }
    return 0;
}
void trovaDim(int nr,int nc, int mat[nr][nc]) {
    dim dimensioni[3];
    int a, b, h, ht,bt,at;
    for (int i = 0; i < 3; ++i) {
        dimensioni[i].val = 0;
    }
    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) {
            ht=0;bt=0;at=0;
            for (h = i; mat[h][j] && h<nr; h++) {
            }

            if (h-i > dimensioni[0].val) {
                dimensioni[0].val = h-i;
                dimensioni[0].x = i;
                dimensioni[0].y = j;
                ht=1;
            }
            for (b = j; mat[i][b] && b<nc; b++) {
            }
            if (b-j > dimensioni[1].val) {
                dimensioni[1].val = b-j;
                dimensioni[1].x = i;
                dimensioni[1].y = j;
                bt=1;
            }

            a=(b-j)*(h-i);
            if(a>dimensioni[2].val){
                dimensioni[2].val = a;
                dimensioni[2].x = i;
                dimensioni[2].y = j;
                at=1;
            }
            if(ht==1) {
                dimensioni[0].b = b-j;
                dimensioni[0].a = a;
            }
            if(bt==1){
                dimensioni[1].h = h-i;
                dimensioni[1].a = a;
            }
            if(at==1){
                dimensioni[2].h = h-i;
                dimensioni[2].b = b-j;
            }
            }
        }

        printf("Altezza massima: (%d,%d), con h=%d, b=%d, a=%d\n", dimensioni[0].x, dimensioni[0].y, dimensioni[0].val,dimensioni[0].b, dimensioni[0].a);
        printf("Base massima: (%d,%d), con h=%d, b=%d, a=%d\n", dimensioni[1].x, dimensioni[1].y, dimensioni[1].h,dimensioni[1].val, dimensioni[1].a);
        printf("Area massima: (%d,%d), con h=%d, b=%d, a=%d\n", dimensioni[2].x, dimensioni[2].y, dimensioni[2].h,dimensioni[2].b,dimensioni[2].val);

    }

int main() {
    FILE* f;
    int nr=0,nc=0;
    f=fopen("mappa.txt","r");
    if(f==NULL) {
        printf("apertura file non avvenuta");
        return 1;
    }
    fscanf(f,"%d %d",&nr,&nc);
    int mat[nr][nc];
    leggiMat(f,nr,nc,mat);
    trovaDim(nr,nc,mat);
    fclose(f);
}
