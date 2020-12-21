//
// Created by davii on 18/12/2020.
//
#include "invArray.h"
struct invArray_s{
    inv_t *invArr;
    int size;
};

invArray_t invArray_init(){
    invArray_t invA = malloc(sizeof(struct invArray_s));
    invA->invArr = NULL;
    invA->size=invA->size=0;
    return invA;
}
void invArray_read(FILE *fp, invArray_t invArray){
    fscanf(fp, "%d" , &invArray->size);
    invArray->invArr = malloc(invArray->size*sizeof(inv_t));
    for (int i = 0; i < invArray->size; ++i) {
        fscanf(fp, "%s %s", invArray->invArr[i].nome,invArray->invArr[i].tipo);
        stat_read(fp, &invArray->invArr[i].stat);
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    for (int i = 0; i < invArray->size; ++i) {
        fprintf(fp, "%s %s", invArray->invArr[i].nome,invArray->invArr[i].tipo);
        stat_print(fp, &invArray->invArr[i].stat, 0);
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    fprintf(fp, "%s %s", invArray->invArr[index].nome, invArray->invArr[index].tipo);
    stat_print(fp, &invArray->invArr[index].stat, 0);
}
int invArray_nOgg(invArray_t invArray){
    return invArray->size;
}
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &invArray->invArr[index];
}




