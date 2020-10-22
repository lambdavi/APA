#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENZE 20
#define MAX_RIGA 200
#define MAX_S 5
#define MAX_OCCUR 10

struct in{
    char parola[MAX_RIGA];
    int index;
};
struct Sp{
    char seq[MAX_S];
    int counter;
    struct in m[MAX_OCCUR];
};

void rimpiazza(char parola[MAX_RIGA], int n,struct Sp d[MAX_OCCUR*n],int z,int j)
{
    for(int i = 0; parola[i]; i++)
        parola[i] = tolower(parola[i]);

    for(int i = 0; d[z].seq[i]; i++)
        d[z].seq[i] = tolower(d[z].seq[i]);

    if(strstr(parola, d[z].seq) != NULL) {
        if (d[z].counter + 1 <= 10) {
            d[z].counter++;
            strcpy(d[z].m[d[z].counter - 1].parola, parola);
            d[z].m[d[z].counter - 1].index = j;
         }
    }
}

char* dividi(char parola[MAX_RIGA]){
    char *token;
    char *p;
    token = strtok(parola, "',.");
    return token;
}

int main()
{
    FILE *s,*t;

    char parola[MAX_RIGA], app[MAX_RIGA],seq[MAX_S];
    int n,j=0;

    s=fopen("sequenze.txt","r+");
    t=fopen("testo.txt","r+");
    if(s==NULL || t==NULL){
        printf("Errore nell'apertura del file.");
        return -1;
    }
    fscanf(s,"%d",&n);

    if(n>MAX_SEQUENZE){
        printf("Troppe sequenze richieste");
        return -1;
    }

    struct Sp d[MAX_OCCUR*n];

    for (int i = 0; i < n; ++i) {
        fscanf(s, "%s", d[i].seq);
        d[i].counter=0;
    }

    while(fscanf(t,"%s",parola)!=EOF){
       j++;
       strcpy(app,dividi(parola));
       for (int z = 0; z < n; ++z)
           rimpiazza(app,n,d,z,j);
    }

    for (int l = 0; l < n; ++l) {
        printf("\n%s->",d[l].seq);
        for (int i = 0; i < d[l].counter; ++i)
            printf("%s (%d), ",d[l].m[i].parola,d[l].m[i].index);
    }

    fclose(s);
    fclose(t);
}