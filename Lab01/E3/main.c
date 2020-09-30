#include <stdio.h>
#include <string.h>
#define nMax 30
void ruotaMat(int *v, int n, int p, char dir[20]) {
    int temp=0;
    for (int k = 0; k < p; ++k) {
        if(strcmp(dir,"sinistra") ==0 || strcmp(dir,"su") == 0){
            temp=v[0];
            for (int i = 0; i < n-1; ++i)
                v[i]=v[i+1];
            v[n-1]=temp;
        }
        else{
            temp=v[n-1];
            for (int i = n-1; i > 0; i--)
                v[i]=v[i-1];
            v[0]=temp;
        }
    }
}
int main() {
    FILE *f;
    int nr,nc,mat[nMax][nMax],app[nMax];
    char str[100],select[20],dir[20];
    int ind,pos=1;
    f=fopen("mat.txt","r+");
    if(f==NULL){return 1;}
    fscanf(f,"%d %d",&nr,&nc);
    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) {
            fscanf(f,"%d",&mat[i][j]);
        }
    }
    printf("Inserisci stringa: ");
    gets(str);
    sscanf(str,"%s %d %s %d",select,&ind,dir,&pos);
    while(strcmp(str,"0")){
        if(strcmp(select,"riga")==0) {
            printf("Lavoro sulla riga\n");
            ruotaMat(mat[ind], nc, pos, dir);
        }
        else{
            printf("Lavoro sulle colonna\n");
            for (int j = 0; j < nr; ++j) {
                app[j]=mat[j][ind];
                //printf("%d ",app[j]);
            }
            ruotaMat(app, nr, pos, dir);
            for (int j = 0; j < nr; ++j) {
                mat[j][ind]=app[j];
            }
        }
        for (int i = 0; i < nr; ++i) {
            for (int j = 0; j < nc; ++j) {
                printf("%d ",mat[i][j]);
            }
            printf("\n");
        }
        printf("\nInserisci stringa: ");
        gets(str);
        sscanf(str,"%s %d %s %d",select,&ind,dir,&pos);
    }
    printf("\n");
    return 0;
}
