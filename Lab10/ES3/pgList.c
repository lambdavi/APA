//
// Created by Davide Buoso on 17/12/20.
//
#include "pg.h"
#include "pgList.h"
typedef struct nodo_pg_t *link;
struct nodo_pg_t{
    pg value;
    link next;
};
struct pgList_s{
    link head;
    link tail;
    int n_pg;
};

link new_pgNode(pg val, link next){
    link x = malloc(sizeof(*x));
    if(x==NULL)
        return NULL;
    else{
        x->value = val;
        x->value.equip = equipArray_init();
        x->next = next;
    }
    return x;
}
void insCoda(link *hp, link *tp, pg val){
    if(*hp==NULL)
        *hp =*tp= new_pgNode(val, NULL);
    else {
        (*tp)->next=new_pgNode(val, NULL);
        *tp = (*tp)->next;
    }
}

pgList_t pgList_init(){
    pgList_t pgL = malloc(sizeof(struct pgList_s));
    pgL->head = pgL->tail = NULL;
    pgL->n_pg = 0;
    return pgL;
}
void pgList_free(pgList_t pgList){
    free(pgList);
}

void pgList_read(FILE *f, pgList_t lista){
    pg temp;
    while (fscanf(f,"%s %s %s", temp.cod, temp.nick, temp.classe)!=EOF){
        stat_read(f, &temp.b_stat);
        insCoda(&lista->head, &lista->tail, temp);
        (*lista).n_pg++;
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link player;
    for (player = pgList->head; player!=NULL; player=player->next)
        pg_print(fp,&player->value, invArray);
}

pg *pgList_searchByCode(pgList_t pgList, char* cod){
    link player;
    for (player = pgList->head; player!=NULL; player=player->next) {
        if(strcmp(player->value.cod, cod)==0){
            return &player->value;
        }
    }
    return NULL;
}

void pgList_insert(pgList_t pgList, pg pg){
    //se non esiste già il codice
    if(pgList_searchByCode(pgList, pg.cod) == NULL)
        insCoda(&pgList->head, &pgList->tail, pg);
    else
        printf("Codice gia' esistente");
}

void pgList_remove(pgList_t pgList, char* cod){
    int found=0;
    link player=pgList->head, prev;
    if(strcmp(player->value.cod, cod)==0 && player!= NULL)
    {
        pgList->head = player->next;   // cambia head
        free(player);               // libera vecchia head
        return;
    }
    for (prev = player; player!=NULL && found == 0; prev = player, player=player->next) {
        if(strcmp(player->value.cod, cod)==0){
            found=1;
            prev->next = player->next;
            free(player);
        }
    }

}




