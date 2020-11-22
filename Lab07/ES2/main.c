#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxStringLen 50
enum fine;
typedef struct{
    int gg, mm, aa;
}Date;

typedef struct{
    int cap;
    char cod[maxStringLen], nome[maxStringLen], cognome[maxStringLen],via[maxStringLen], citta[maxStringLen];
    Date data;
}Item;
typedef struct node *link;
struct node {
    Item val;
    link next;
};
link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}
void clear(){
    for (int i = 0; i < 3; ++i) {
        printf("\n");
    }
}
int greater(Date x, Date y){
    if(x.aa>y.aa) return 0;
    else if(x.aa==y.aa && x.mm>y.mm) return 0;
    else if(x.aa==y.aa && x.mm==y.mm && x.gg>y.gg) return 0;
    return 1;
}
link SortListIns(link h, Item val) {
    link x, p;
    Date k = val.data;
    if (h==NULL || greater(h->val.data,k)==1)
        return newNode(val, h);
    for (x=h->next, p=h;
         x!=NULL && greater(k,x->val.data)==1;
         p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}
// CoE=cerca o elimina | 0- Cerca, 1- elimina
// CoD=Codice o Data | 3 o 4- Ricerca per codice 5- Ricerca per Data
// Compreso tra due date estremi ESCLUSI
Item find_byCode(link *h, char *cod, int CoE, int QoC, Date d1, Date d2) {
    link *x=h,m;
    Item send;
    send.cap = -1;
    while (*x!=NULL){
        if(QoC!=5){
            if(strcmp(cod,(*x)->val.cod)==0){
                if(CoE==1) {
                    m = *x;
                    *x = (*x)->next;
                    send = m->val;
                    free(m);
                }
                else{
                    m = *x;
                    send = m->val;
                }
                break;
            }
        }
        else{
            if(greater((*x)->val.data,d1)==0 && greater(d2,(*x)->val.data)==0){
                    m = *x;
                    *x = (*x)->next;
                    send = m->val;
                    free(m);
                break;
            }
        }

        x = &((*x)->next);
    }
    return send;
}
void stampaListaVideo(link h){
    link stampa=h;
    while(stampa!=NULL){
            printf("Codice: %s\n", stampa->val.cod);
            printf("Nome: %s\n", stampa->val.nome);
            printf("Cognome: %s\n", stampa->val.cognome);
            printf("Data di nascita %d/%d/%d:\n", stampa->val.data.gg, stampa->val.data.mm, stampa->val.data.aa);
            printf("Via: %s\n", stampa->val.via);
            printf("Citta': %s\n", stampa->val.citta);
            printf("Cap: %d\n\n\n", stampa->val.cap);
            stampa = stampa->next;
    }
}
void stampaListaFile(FILE *f, link h){
    link stampa=h;
    while(stampa!=NULL){
        fprintf(f,"Codice: %s\n", stampa->val.cod);
        fprintf(f,"Nome: %s\n", stampa->val.nome);
        fprintf(f,"Cognome: %s\n", stampa->val.cognome);
        fprintf(f,"Data di nascita %d/%d/%d:\n", stampa->val.data.gg, stampa->val.data.mm, stampa->val.data.aa);
        fprintf(f,"Via: %s\n", stampa->val.via);
        fprintf(f,"Citta': %s\n", stampa->val.citta);
        fprintf(f,"Cap: %d\n\n\n", stampa->val.cap);
        stampa = stampa->next;
    }
}
int menu(){
    clear();
    int scelta;
    printf("> Benvenuto <\n");
    printf("Scegli l'operazione che vuoi eseguire: (scrivere qualsiasi altro numero per uscire)\n");
    printf("1. Acquisizione elemento da tastiera.\n");
    printf("2. Acquisizione elemento da file.\n");
    printf("3. Ricerca per codice in un elemento.\n");
    printf("4. Ricerca per codice in un elemento e cancellazione.\n");
    printf("5. Cancellazione tra due date.\n");
    printf("6. Stampa lista su file.\n");
    scanf("%d", &scelta);
    printf("\n");
    return scelta;
}
int main()
{
    int s,end=0,cont=0;
    char filename[30];
    Item send, found;
    Date d1,d2;
    //Azzero date che userò come variabili temporanee
    d1.aa=d1.mm=d1.gg=d2.aa=d2.mm=d2.gg=0;
    link head=NULL, elem=NULL;
    s=(menu());
    FILE *f1, *f2;
    while (s!=0){
        switch(s){
            case 1: printf("Inserisci codice: ");
                scanf("%s", send.cod);
                printf("Inserisci nome: ");
                scanf("%s", send.nome);
                printf("Inserisci cognome: ");
                scanf("%s", send.cognome);
                printf("Inserisci data di nascita(gg/mm/aa): ");
                scanf("%d/%d/%d", &send.data.gg, &send.data.mm, &send.data.aa);
                printf("Inserisci via: ");
                scanf("%s", send.via);
                printf("Inserisci citta': ");
                scanf("%s", send.citta);
                printf("Inserisci cap: ");
                scanf("%d", &send.cap);
                head=SortListIns(head,send);
                break;
            case 2:
                printf("Inserisci nome del file: ");
                scanf("%s", filename);
                f1=fopen(filename, "r+");
                if(f1==NULL) {
                    fprintf(stderr, "\nIl file non e' stato aperto correttamente\n");
                    return EXIT_FAILURE;
                }
                while(fscanf(f1,"%s %s %s %d/%d/%d %s %s %d",send.cod, send.nome,  send.cognome,&send.data.gg,
                             &send.data.mm, &send.data.aa, send.via, send.citta, &send.cap)!=EOF){
                    head=SortListIns(head,send);

                }
                break;
            case 3:printf("Inserisci codice: ");
                    scanf("%s", send.cod);
                    found=find_byCode(&head, send.cod,0,s, d1, d2);
                    if(found.cap!=-1){
                        elem=SortListIns(elem, found);
                        stampaListaVideo(elem);
                    }
                    else
                        printf("Non trovato.");

            case 4:printf("Inserisci codice: ");
                scanf("%s", send.cod);
                found=find_byCode(&head, send.cod,1,s,d1,d2);
                if(found.cap!=-1){
                    elem=SortListIns(elem, found);
                    stampaListaVideo(elem);
                }
                else
                    printf("Non trovato.");
                break;
            case 5: printf("Inserisci data 1: ");
                    scanf("%d/%d/%d", &d1.gg, &d1.mm, &d1.gg);
                    printf("Inserisci data 2: ");
                    scanf("%d/%d/%d", &d2.gg, &d2.mm, &d2.gg);
                    while (end==0) {
                        found.cap=0;
                        found = find_byCode(&head, send.cod, 1, s, d1, d2);
                        if (found.cap != -1) {
                            elem = SortListIns(elem, found);
                            cont++;
                        } else {
                            end = 1;
                            printf("Fine. %d elementi eliminati", cont);
                        }
                    }
                    break;
            case 6:
                f2=fopen("stampata.txt", "w+");
                if(f2==NULL) {
                    fprintf(stderr, "\nIl file non e' stato aperto correttamente\n");
                    return EXIT_FAILURE;
                }
                stampaListaFile(f2,head);
                break;
            default:
                s=0;
                fclose(f2);
                fclose(f1);
                break;
        }
        s=(menu());
    }
    stampaListaVideo(head);
    return 0;
}