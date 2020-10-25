#include <stdio.h>
#define N 7
int cont(int *v, int r, int c, int flag){
    int ris = 0;
    if (flag == 1)
        for (int k = 0; k < r; ++k,v++) {
            if(*v==c){ris++;}
        }
    else
        for (int i = r; i > N-r; i--)
            if(*v==c){ris++;}
    return ris;
}
int trovaMaggioritario(int *v, int r){
    int mid=r/2, left, right;
    if(r == 1) return v[0];
    left = trovaMaggioritario(v,mid);
    right = trovaMaggioritario(v+mid,r-mid);

    if(left==right)
        return left;
    int c1 = cont(v,mid,left, 1);
    int c2 = cont(v+mid,r-mid,right, 0);
    return c1 > c2 ? left : right;
}

int main() {
    int vet[N]={3, 4, 4, 4, 3, 4, 3};
    int num =trovaMaggioritario(vet,N);
    int contatore =cont(vet,N,num, 1);
    printf("Il maggioritario e':  %d", contatore > N/2 ? num : -1);
    return 0;
}
