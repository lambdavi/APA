//
// Created by Davide Buoso on 18/12/20.
//
#include "equipArray.h"
#include "pg.h"
struct equipArray_s{
    int equipIndexes[EQUIP_SLOT];
    int nOgg;
};
equipArray_t equipArray_init(){
    equipArray_t eA = malloc(sizeof(struct equipArray_s));
    eA->nOgg =0;
    return eA;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->nOgg;
}
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    if(equipArray->nOgg > 0)
        for (int i = 0; i < equipArray->nOgg; ++i) {
            printf("%d) ", i+1);
            invArray_printByIndex(fp, invArray, equipArray->equipIndexes[i]);
        }
}
void equipArray_add(equipArray_t equipArray, int index){
    if(equipArray->nOgg != EQUIP_SLOT) {
        equipArray->equipIndexes[equipArray->nOgg] = index;
        equipArray->nOgg++;
    }
}
void equipArray_del(equipArray_t equipArray, int index) {
    for (int i = index - 1; i < equipArray->nOgg; i++)
        equipArray->equipIndexes[i] = equipArray->equipIndexes[i + 1];
    equipArray->nOgg--;
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->equipIndexes[index];
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int risp;
    for (int i = 0; i < invArray_nOgg(invArray); ++i) {
        printf("%d) ",i+1);
        invArray_printByIndex(stdout, invArray, i);
    }
    printf("Scegli oggetto da inserire: ");
    scanf("%d", &risp);
    if(risp<1 && risp>invArray_nOgg(invArray)) {
        printf("Indice non esistente");
        return;
    }
    equipArray_add(equipArray, risp-1);
}



