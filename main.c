#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct dict{
    char ricod[20];
    char orig[20];
}dict;
char *rimpiazza(char *str, char *strVecchia, char *strNuova)
{
    static char buff[200];
    char *p;
    //Imposto un puntatore dove trovo la corrispondenza
    if(!(p = strstr(str, strVecchia)))
        return str;
    //copio in buff la parte prima di quella che deve essere sostituita
    strncpy(buff, str, p-str);
    //inizio a scrivere su buff la nuova stringa a poi il resto della vecchia stringa 
    sprintf(buff+(p-str), "%s%s", strNuova, p+strlen(strVecchia));
    return buff;
}
int main() {
    FILE *f1,*f2,*f3;
    int S=0;
    char str[200],str2[200];
    
    f1=fopen("sorgente.txt","r+");
    f2=fopen("dizionario.txt","r+");
    f3=fopen("ricondizionato.txt","w");
    
    if(f1==NULL){printf("\nErrore nell'apertura del file 1\n"); exit(EXIT_FAILURE);}
    if(f2==NULL){printf("\nErrore nell'apertura del file 2\n"); exit(EXIT_FAILURE);}
    
    fscanf(f2,"%d",&S);
    dict dizionario[S];
    //Leggo il file dizionario e salvo nella struct
    for(int i=0;i<S;i++){
        fscanf(f2,"%s %s",dizionario[i].ricod, dizionario[i].orig);
    }
    //Leggo una riga alla volta del file sorgente e sostituisco le parole
    while(fgets(str,200,f1)!=NULL){
        strcpy(str2,rimpiazza(str,dizionario[0].orig,dizionario[0].ricod));
        for (int i = 1; i < S; ++i) {
            if (strstr(str, dizionario[i].orig) != NULL) {
                printf("%s, %s, %s\n",str,dizionario[i].ricod, dizionario[i].orig);
                strcpy(str2,rimpiazza(str2,dizionario[i].orig,dizionario[i].ricod));
            }
        }
        fputs(str2,f3);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}
