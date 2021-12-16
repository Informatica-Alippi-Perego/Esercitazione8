#include <stdlib.h>
#include <stdio.h>
#include <string.h>

File strutturato come segue
 
 Numero_viaggi 6
 Anno   km_percorsi mezzo_di_trasporto
 2001   4000    0
 2004   3000    1
 2007   4000    0
 2010   6000    1
 2012   1000    0
 2013   8000    1
 
 Uscita:
 Nr. di viaggi nel 2009-2013: 3
 
 Visualizza pnt millemiglia
 La famiglia Bianchi ha guadagnato 3000 punti millemiglia
 

typedef struct viaggio {
    int anno;
    int km;
    int mezzo;
} viaggio;

void creaFileIniziale(void);

int leggiNumViaggi(char nomeFile[]);
void leggiFile(char nomeFile[], viaggio *viaggi, int numViaggi);

int main(){
    viaggio *viaggi = NULL;
    int numViaggi;
    
    creaFileIniziale();
    
    numViaggi = leggiNumViaggi("bianchi.txt");
    printf("Numero di righe nel file: %d\n",numViaggi);
    if (numViaggi>0)
        leggiFile("bianchi.txt", viaggi, numViaggi);
    
    return 0;
}

void creaFileIniziale(void){
    FILE *f;
    f= fopen("bianchi.txt","w");
    fprintf(f,"Numero_viaggi\t6\n");
    fprintf(f,"Anno\tkm_percorsi\tmezzo_di_trasporto\n");
    fprintf(f,"2001\t4000\t0\n");
    fprintf(f,"2004\t3000\t1\n");
    fprintf(f,"2007\t4000\t0\n");
    fprintf(f,"2010\t6000\t1\n");
    fprintf(f,"2012\t1000\t0\n");
    fprintf(f,"2013\t8000\t1\n");
    fclose(f);
}

int leggiNumViaggi(char nomeFile[]){
    FILE *f;
    int n_righe;
    char intestazione[20];
    
    f = fopen(nomeFile,"r");
    if (f==NULL){
        printf("Errore apertura file\n");
        return -1;
    }
    fscanf(f, "%s", intestazione);
    fscanf(f, "%d", &n_righe);
        
    fclose(f);
    
    return n_righe;
}

void leggiFile(char nomeFile[], viaggio *viaggi, int numViaggi){
    FILE *f;
    char stringa[20];
    int n;
    int i;
    int punti = 0;
    int numViaggio2009 = 0;
    
    f = fopen(nomeFile, "r");
    if (f==NULL)
        return;
    
    fscanf(f, "%s", stringa);
    fscanf(f, "%d", &n);
    fscanf(f, "%s", stringa); //anno
    fscanf(f, "%s", stringa); //km_percorsi
    fscanf(f, "%s", stringa); //mezzo_di_trasporto
    
    viaggi = (viaggio*)malloc(sizeof(viaggio)*numViaggi);
    //while(!feof(f))
    for (i=0; i<numViaggi && !feof(f); i++){
        fscanf(f, "%d", &viaggi[i].anno);
        fscanf(f, "%d", &viaggi[i].km);
        fscanf(f, "%d", &viaggi[i].mezzo);
        
        if (viaggi[i].mezzo == 0)
            punti = punti + viaggi[i].km/3;
        
        if ((viaggi[i].anno>=2009) && (viaggi[i].anno <= 2013))
            numViaggio2009++;
    }
    fclose(f);
    
    printf("La famiglia Bianchi ha guadagnato %d punti millemiglia\n",punti);
    
    f = fopen("dati.dat","w");
    if (f==NULL)
        return;
    fprintf(f,"Nr. di viaggi nel 2009-2013: %d",numViaggio2009);
    fclose(f);
    free(viaggi);
    
}
