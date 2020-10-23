#include <stdio.h>
#include <math.h>


int little_o_big(){
    int n = 1;
    return *(char *)&n;
}
void stampa_dim(float af, double ad, long double ald){
    printf("\nByte: %llu bit: %llu\n",sizeof(af),sizeof(af)*8);
    printf("Byte: %llu bit: %llu\n",sizeof(ad),sizeof(ad)*8);
    printf("Byte: %llu bit: %llu\n",sizeof(ald),sizeof(ald)*8);
}
void stampaCodifica(void *p, int size, int b_o_l) {
    int temp[size], i, j, k, final[size*8];
    unsigned char *c = p;

    for (i = 0; i < size; ++i) { temp[i] = *(c + i); }

    if(!b_o_l)
        for (i = 0; i < size; i++) {
            for (j = 0, k = 7; k >=0; j++, k--) {
                final[j] = temp[i] % 2;
                temp[i] = floor(temp[i] / 2);
            }
        }
    else
        for (i = size -1; i >=0; i--) {
            for (j =(8 * (size - i)) - 1, k = 0; k < 8; j--, k++) {
                final[j] = temp[i] % 2;
                temp[i] = floor(temp[i] / 2);
            }
        }

    if (size != 16) {
        printf("Segno: ");
        for (i = 0; i < size * 8 - 1; i++) {
            if (i == 1) { printf("\nEsponente: "); }
            else if (i == 9 && size == 4) { printf("\nMantissa: "); }
            else if (i == 12 && size == 8) { printf("\nMantissa: "); }
            printf("%d", final[i]);
        }
    }
    else{
        printf("Segno: ");
        for (int l = 48; l < size*8-1; ++l) {
            if(l==49){ printf("\nEsponente: "); }
            else if(l==64){printf("\nMantissa: ");}
            printf("%d",final[l]);
        }
    }
    printf("\n\n");
}
int main() {
    int bigEndian=little_o_big();
    printf(bigEndian?"Little Endian\n":"Big Endian\n");
    float af = 0;
    double ad = 0;
    long double ald=0;
    stampa_dim(af, ad, ald);
    printf("Inserire numero: ");
    scanf("%f", &af);
    stampaCodifica ((void*)&af,sizeof(af),bigEndian);
    ad=(double)af;
    stampaCodifica ((void*)&ad,sizeof(double),bigEndian);
    ald = (long double)af;
    stampaCodifica((void*)&ald,sizeof(long double),bigEndian);
    return 0;
}

