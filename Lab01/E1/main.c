#include <stdio.h>
const int nMAX = 20;
const int mMAX = 20;

int findmax(int n, int v[n]){
    int max=0,team=0;
    for (int i = 0; i < n; ++i) {
        if(v[i]>max){max=v[i];team=i;}
    }
    return team;
}
void disp(int nr, int nc, int mat[][mMAX]){
    printf("\n");
    for (int k = 0; k < nr; ++k) {
        printf("Team %d: ",k+1);
        for (int i = 0; i < nc; ++i) {
            printf("%d ",mat[k][i]);
        }
        printf("\n");
    }
}
void readF(FILE *fp, int n, int c, int mat[][mMAX]){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < c; ++j) {
            fscanf(fp,"%d",&mat[i][j]);
        }
    }
}
int main() {
    FILE* f;
    int mat[nMAX][mMAX],n,m;
    f = fopen("mat.txt", "r+") ;
    if(f== NULL){
        printf("Error in opening file.\n");
        return 1;
    }
    fscanf(f, "%d %d",&n,&m);
    if(n>nMAX||m>nMAX){printf("Error in input\n"); return -1;};
    int leaderboard[n];
    for (int k = 0; k < n; ++k) {
        leaderboard[k]=0;
    }
    readF(f,n,m,mat);
    disp(n,m,mat);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            leaderboard[j]+=mat[j][i];
        }
        printf("\nLa capolista, nella giornata numero %d, e' la squadra %d\n",i+1,findmax(n,leaderboard)+1);
    }
    for (int k = 0; k < n; ++k) {
        printf("%d ",leaderboard[k]);
    }
    fclose(f);
    return 0;
}