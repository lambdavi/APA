#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxLen 30
#define maxLenComando 15
enum comando_e{r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine};
typedef struct{
    int gg,mm,aa;
}Date;
typedef struct{
    int rit;
    char cod[maxLen],par[maxLen],dest[maxLen], oraP[10], oraA[10];
    Date data;
}t;
void riempiStruct(FILE *f,int n,t trat[n]){
    for (int i = 0; i < n; ++i) {
        fscanf(f,"%s %s %s %d/%d/%d %s %s %d",trat[i].cod,trat[i].par, trat[i].dest, &trat[i].data.aa, &trat[i].data.gg,&trat[i].data.mm, trat[i].oraP,
                trat[i].oraA, &trat[i].rit);
    }
    /*for (int i = 0; i < n; ++i) {
        printf("%s %s %s %d/%d/%d %s %s %d\n",trat[i].cod,trat[i].par, trat[i].dest, trat[i].data.aa, trat[i].data.gg,trat[i].data.mm, trat[i].oraP,
               trat[i].oraA, trat[i].rit);
    }*/

}
int comparaDate(Date a, Date b)
{
    if (a.aa < b.aa) return 1;
    if (a.aa == b.aa && a.mm < b.mm) return 1;
    if (a.aa == b.aa && a.mm == b.mm && a.gg <= b.gg) return 1;
    return 0;
}
int leggiComando(){
    int scelta=5;
    char risp[maxLenComando];
    printf("Scegli operazione da eseguire: (scrivere uno dei comandi, ogni comando non presnete nella lista "
           "terminera' l'esecuzione)\n");
    printf("date:\t\telencare tutte le corse partite in un certo intervallo di date\n");
    printf("partenza:\telencare tutte le corse partite da una certa fermata\n");
    printf("capolinea:\telencare tutte le corse che fanno capolinea in una certa fermata\n");
    printf("ritardo:\telencare tutte le corse che hanno raggiunto la destinazione in ritardo in un certo intervallo di "
           "date\n");
    printf("ritardo_tot:\telencare il ritardo complessivo accumulato dalle corse identificate da un certo "
           "codice di tratta\n");
    printf("fine:\t\tesci dal programma\n");
    printf("Scelta: ");
    scanf("%s",risp);
    if(strcmp(risp,"date")==0)
        scelta=r_date;
    if(strcmp(risp,"partenza")==0)
        scelta=r_partenza;
    if(strcmp(risp,"capolinea")==0)
        scelta=r_capolinea;
    if(strcmp(risp,"ritardo")==0)
        scelta=r_ritardo;
    if(strcmp(risp,"ritardo_tot")==0)
        scelta=r_ritardo_tot;
    if(strcmp(risp,"fine")==0)
        scelta=r_fine;
    return scelta;
}
void trovaDate(char dataP[11], char dataF[11], int n, t trat[n]){
    Date a, c;
    sscanf(dataP,"%d/%d/%d",&a.aa,&a.gg,&a.mm);
    sscanf(dataF,"%d/%d/%d",&c.aa,&c.gg,&c.mm);

    for (int i = 0; i < n; ++i) {
        if(comparaDate(a, trat[i].data) && comparaDate(trat[i].data, c))
            printf("%s %s %s %d/%d/%d %s %s %d\n",trat[i].cod,trat[i].par, trat[i].dest, trat[i].data.aa,
                    trat[i].data.gg,trat[i].data.mm, trat[i].oraP, trat[i].oraA, trat[i].rit);
    }
}
void trovaCorse(char fermata[maxLen],int n, t trat[n]){
    int trovato =0;
    for (int i = 0; i < n; ++i) {
        if(strcmp(fermata,trat[i].par)==0) {
            printf("%s %s %s %d/%d/%d %s %s %d\n", trat[i].cod, trat[i].par, trat[i].dest, trat[i].data.aa,
                   trat[i].data.gg, trat[i].data.mm, trat[i].oraP, trat[i].oraA, trat[i].rit);
            trovato=1;
        }
    }
    if(trovato==0)
        printf("Capolinea non trovato.\n");
}
void trovaCapolinea(char capo[maxLen],int n, t trat[n]){
    int trovato=0;
    for (int i = 0; i < n; ++i) {
        if(strcmp(capo,trat[i].dest)==0){
            printf("%s %s %s %d/%d/%d %s %s %d\n",trat[i].cod,trat[i].par, trat[i].dest, trat[i].data.aa,
                   trat[i].data.gg,trat[i].data.mm, trat[i].oraP, trat[i].oraA, trat[i].rit);
            trovato=1;
        }
    }
    if(trovato==0)
        printf("Capolinea non trovato.\n");
}
void trovaRitardo(char dataP[11], char dataF[11],int n, t trat[n]){
    Date a, c;
    sscanf(dataP,"%d/%d/%d",&a.aa,&a.gg,&a.mm);
    sscanf(dataF,"%d/%d/%d",&c.aa,&c.gg,&c.mm);

    for (int i = 0; i < n; ++i) {
        if(comparaDate(a, trat[i].data) && comparaDate(trat[i].data, c) && trat[i].rit==0)
            printf("%s %s %s %d/%d/%d %s %s %d\n",trat[i].cod,trat[i].par, trat[i].dest, trat[i].data.aa,
                   trat[i].data.gg,trat[i].data.mm, trat[i].oraP, trat[i].oraA, trat[i].rit);
    }

}
void trovaRitardoTot(char codice[maxLen], int n, t trat[n]){
    int somma=0;
    int found=0;
    for (int i = 0; i < n; ++i) {
        if(strcmp(codice,trat[i].cod)==0) {
            printf("%s %s %s con ritardo: %d\n",trat[i].cod,trat[i].par, trat[i].dest,  trat[i].rit);
            somma += trat[i].rit;
            found=1;
        }
    }
    if(found==0)
        printf("Nessuna tratta trovata\n");
    else
        printf("Ritardo accumulato %d\n",somma);

}
void selezionaDati(int n, t trat[n]){
    int s=0;
    char d1[15], d2[15],temp[maxLen];
    s=leggiComando();
    while(s!=5) {
        switch (s) {
            case 0:
                printf("Inserisci data iniziale: ");
                scanf("%s", d1);
                printf("Inserisci data finale: ");
                scanf("%s", d2);
                trovaDate(d1, d2, n, trat);
                break;
            case 1:
                printf("Inserisci fermata: ");
                scanf("%s", temp);
                trovaCorse(temp, n, trat);
                break;
            case 2:
                printf("Inserisci capolinea: ");
                scanf("%s", temp);
                trovaCapolinea(temp, n, trat);
                break;
            case 3:
                printf("Inserisci data iniziale: ");
                scanf("%s", d1);
                printf("Inserisci data finale: ");
                scanf("%s", d2);
                trovaRitardo(d1,d2, n,trat);
                break;
            case 4:
                printf("Inserisci codice tratta: ");
                scanf("%s",temp);
                trovaRitardoTot(temp,n, trat);
                break;
            default:
                printf("Fine programma");
                break;
        }
        system("pause");
        printf("\n");
        s=leggiComando();
    }
}

int main() {
    FILE *f;
    int n;
    char risp[15];

    f=fopen("log.txt","r+");
    if(f==NULL) return 1;
    fscanf(f,"%d",&n);
    t tratte[n];
    riempiStruct(f,n,tratte);
    selezionaDati(n,tratte);
    fclose(f);

    return 0;
}
