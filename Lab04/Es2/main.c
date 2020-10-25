#include <stdio.h>
#define N 8
int cont(int *v, int l, int r, int c){
    int ris = 0;
    for (int k = l; k < r; ++k,v++) {
        if(*v==c){ris++;}
    }
    return ris;
}
int trovaMaggioritario(int *v, int l, int r){
    int mid, left, right;
    if(l == r)
        return *(v+l);
    mid = (l+r)/2;
    left = trovaMaggioritario(v, l, mid);
    right = trovaMaggioritario(v,mid+1,r);
    if(left==right)
        return left;
    return cont(v,l,mid,left)>cont(v,mid+1,r,right)?left:right;
}
int maggioritario(int *v, int r){
    int num = trovaMaggioritario(v,0,r);
    if (cont(v,0,r,num)>(r/2))
        return num;
    else
        return -1;
}

int main() {
    int vet[N]={0, 0, 0, 2, 0, 4, 0, 5};
    printf("Il maggioritario e':  %d", maggioritario(vet,N));
    return 0;
}
