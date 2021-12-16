#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct prodotto{
    char nome[20];
    char codice[20];
    float sconto;
    float prezzo;
    int quantita;
} prodotto;

int inserisciProdotto(prodotto array[], int len);
int checkCodiceProdotto(prodotto array[], int len, char codice[]);
int cercaProdotto(prodotto array[], int len, char codice[], prodotto *trovato);
void eliminaFiniti(prodotto array[], int *len, prodotto finiti[], int *lenFiniti);
void salvaSuFile(prodotto array[], int len, char nomeFile[]);
int caricaDaFile(prodotto array[], char nomeFile[]);

int main(){
    
    return 0;
}

int inserisciProdotto(prodotto array[], int len){
    printf("Inserisci un nuovo prodotto: ");
    fpurge(stdin); //win fflush(stdin);
    gets(array[len].nome);
    do{
        printf("Inserisci codice: ");
        scanf(" %s",array[len].codice);
        if (checkCodiceProdotto(array, len, array[len].codice)==1)
            printf("Errore, codice prodotto già presente\n");
    }while(checkCodiceProdotto(array, len, array[len].codice));
    printf("Inserisci prezzo: ");
    scanf("%f",&(array[len].prezzo));
    printf("Inserisci sconto: ");
    scanf("%f",&array[len].sconto);
    printf("Inserisci quantità: ");
    scanf("%d",&array[len].quantita);
    return len+1;
}

int checkCodiceProdotto(prodotto array[], int len, char codice[]){
    int i;
    for (i=0; i<len; i++){
        if (strcmp(codice,array[i].codice)==0)
            return 1;
    }
    return 0;
}

int cercaProdotto(prodotto array[], int len, char codice[], prodotto *trovato){
    int i;
    for (i=0; i<len; i++){
        if (strcmp(codice,array[i].codice)==0)
        {
            *trovato = array[i];
            //Stampare
            printf("Il prezzo di %s scontato è %.2f\n",array[i].nome,(*trovato).prezzo- trovato->prezzo*trovato->sconto/100.0);
            return 1;
        }
    }
    return 0;
}

void eliminaFiniti(prodotto array[], int *len, prodotto finiti[], int *lenFiniti){
    int i,j;
    
    for (i=0; i<*len; i++){
        if (array[i].quantita==0){
            finiti[*lenFiniti] = array[i];
            (*lenFiniti)++;
            for (j=i; j<*len-1; j++)
                array[j] = array[j+1];
            (*len)--;
        }
    }
}

void salvaSuFile(prodotto array[], int len, char nomeFile[]){
    int i;
    FILE *f;
    
    f = fopen(nomeFile,"w");
    if (f==NULL){
        printf("Errore nel file\n");
        return;
    }
    fprintf(f,"MAGAZZINO\n");
    for (i=0; i<len; i++){
        fprintf(f,"%s %s %.2f %.2f %d",array[i].nome,array[i].codice, array[i].prezzo,array[i].sconto, array[i].quantita);
    }
    fclose(f);
}

int caricaDaFile(prodotto array[], char nomeFile[]){
    FILE *f;
    int i = 0;
    char stringaInutile[20];
    
    f = fopen(nomeFile, "r");
    if (f==NULL)
        return -1;
    
    fscanf(f,"%s",stringaInutile);
    while(!feof(f)){
        fscanf(f, "%s",array[i].nome);
        fscanf(f, "%s",array[i].codice);
        fscanf(f, "%f",&array[i].prezzo);
        fscanf(f, "%f",&array[i].sconto);
        fscanf(f, "%d",&array[i].quantita);
        i++;
    }
    fclose(f);
    return i;
}

int caricaDaFile2(prodotto *array, char nomeFile[]){
    FILE *f;
    int i = 0;
    char stringaInutile[20];
    prodotto temp;
    
    f = fopen(nomeFile, "r");
    if (f==NULL)
        return -1;
    
    fscanf(f,"%s",stringaInutile);
    while(!feof(f)){
        fscanf(f, "%s",temp.nome);
        fscanf(f, "%s",temp.codice);
        fscanf(f, "%f",&temp.prezzo);
        fscanf(f, "%f",&temp.sconto);
        fscanf(f, "%d",&temp.quantita);
        i++;
    }

    fclose(f);
    
    array = (prodotto*)malloc(sizeof(prodotto)*i);
    f = fopen(nomeFile, "r");
    if (f==NULL)
        return -1;
    
    i = 0;
    fscanf(f,"%s",stringaInutile);
    while(!feof(f)){
        fscanf(f, "%s",array[i].nome);
        fscanf(f, "%s",array[i].codice);
        fscanf(f, "%f",&array[i].prezzo);
        fscanf(f, "%f",&array[i].sconto);
        fscanf(f, "%d",&array[i].quantita);
        i++;
    }
    fclose(f);
    return i;
}
