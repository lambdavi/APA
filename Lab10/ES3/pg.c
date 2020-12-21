//
// Created by Davide Buoso on 18/12/20.
//

#include "pg.h"

void pg_print(FILE *fp, pg *pgp, invArray_t invArray){
    fprintf(fp, "%s %s %s", pgp->cod, pgp->nick, pgp->classe);
    if(equipArray_inUse(pgp->equip)>0)
        stat_print(fp, &pgp->eq_stat, 1);
    else
        stat_print(fp, &pgp->b_stat, 1);

    //equipArray_print(fp, pgp->equip, invArray);
}
void pg_clean(pg *pgp){
    equipArray_free(pgp->equip);
}

int pg_read(FILE *fp, pg *pgp){
    if(fscanf(fp, "%s %s %s", pgp->cod, pgp->nick, pgp->classe)!=3)
        return 0;
    stat_read(fp,&pgp->b_stat);
    if(pgp->b_stat.hp < 0 || pgp->b_stat.def < 0 || pgp->b_stat.atk < 0 || pgp->b_stat.mp < 0 || pgp->b_stat.mag < 0 || pgp->b_stat.spr < 0)
        return 0;

    return 1;
}

void pg_updateEquip(pg *pgp, invArray_t invArray){
    int risp;
    printf("Vuoi aggiungere(0) o eliminare(1) un oggetto?");
    scanf("%d", &risp);
    if(risp==0) { // AGGIUNTA OGGETTO
        equipArray_update(pgp->equip, invArray);
        if (equipArray_inUse(pgp->equip) == 1){
            pgp->eq_stat = stat_update(&pgp->b_stat, inv_getStat(invArray_getByIndex(invArray,
                                                                                     equipArray_getEquipByIndex(
                                                                                             pgp->equip,
                                                                                             equipArray_inUse(
                                                                                                     pgp->equip) -
                                                                                             1))));
            printf("\nOggetto aggiunto: ");
            inv_print(stdout, invArray_getByIndex(invArray,equipArray_getEquipByIndex(pgp->equip, equipArray_inUse(pgp->equip)-1)));

        }
        else if(equipArray_inUse(pgp->equip) >= 1){
            pgp->eq_stat = stat_update(&pgp->eq_stat, inv_getStat(invArray_getByIndex(invArray,
                                                                                     equipArray_getEquipByIndex(
                                                                                             pgp->equip,
                                                                                             equipArray_inUse(
                                                                                                     pgp->equip) -
                                                                                             1))));
            printf("\nOggetto aggiunto: ");
            inv_print(stdout, invArray_getByIndex(invArray,equipArray_getEquipByIndex(pgp->equip, equipArray_inUse(pgp->equip)-1)));
        }
    }
    else{ // ELIMINAZIONE OGGETTO
        if(equipArray_inUse(pgp->equip)>0){
            printf("Elementi attualmente equipaggiati: \n");
            equipArray_print(stdout, pgp->equip, invArray);
            printf("Scegli oggetto da eliminare: ");
            scanf("%d", &risp);
            if(risp>0 && risp <= equipArray_inUse(pgp->equip)){
                equipArray_del(pgp->equip, risp);
            }
        }
        else
            printf("Non ci sono ancora oggetti.");
    }

}
