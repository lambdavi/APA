#include <stdio.h>
int little_o_big(){
    int n = 1;
    return *(char *)&n;
}
void stampa_dim(float af, double ad, long double ald){
    printf("\nByte: %llu bit: %llu\n",sizeof(af),sizeof(af)*8);
    printf("Byte: %llu bit: %llu\n",sizeof(ad),sizeof(ad)*8);
    printf("Byte: %llu bit: %llu\n",sizeof(ald),sizeof(ald)*8);
}
void show_ieee754 (void *p, int size) {
    unsigned char * c;
    int i,j;
    c = ((unsigned char*) p) + size - 1;
    printf("Sign: ");
    for(i = size - 1; i > -1; --i, --c){
        for(j = 7; j > -1; --j){
            if((size - 1 - i)*8 + 7 - j == 1){ printf("\nExp: "); }
            else if(size ==  4 && (size - 1 - i)*8 + 7 - j ==  9){ printf("\nMantissa: "); }
            else if(size ==  8 && (size - 1 - i)*8 + 7 - j == 12){ printf("\nMantissa: "); }
            else if(size == 10 && (size - 1 - i)*8 + 7 - j == 16){ printf("\nMantissa: "); }
            printf("%d", (*c >> j)&0x01);
        }
    }
    printf("\n");
}
int main() {
    int bigEndian=little_o_big();
    printf(bigEndian?"Little Endian\n":"Big Endian\n");
    float af = 0;
    double ad = 0;
    long double ald=0;
    stampa_dim(af, ad, ald);
    printf("Inserire numero float: ");
    scanf("%f", &af);
    show_ieee754 ((void*)&af,sizeof(af));

    printf("Inserire numero double: ");
    scanf("%lg", &ad);
    show_ieee754 ((void*)&ad,sizeof(ad));

    printf("Inserire long double: ");
    scanf("%Lg", &ald);
    show_ieee754 ((void*)&ald,sizeof(ald));
    return 0;
}

