#include <stdio.h>
#include <stdlib.h>

int scriviFile(char nomeFile[20], float M);

int main(int argc, const char * argv[]) {
    int num;
    num = scriviFile("input.txt", 2);
    printf("Righe scritte = %d\n",num);
    return 0;
}

int scriviFile(char nomeFile[20], float M){
    FILE *in;
    FILE *out;
    
    int cont = 0;
    double x1,x2,y1,y2;
    double m;
    int primaLettura = 1;
    
    in = fopen(nomeFile,"r");
    if (in == NULL){
        printf("Errore apertura file\n");
        return -1;
    }
    out = fopen("rette.txt", "w");
    if (out == NULL){
        printf("Errore apertura file\n");
        return -1;
    }
    
    fscanf(in,"%lf",&x1);
    while(!feof(in)){
        if (primaLettura == 1){
            fscanf(in,"%lf %lf %lf",&y1,&x2,&y2);
            primaLettura = 0;
        }
        else
            fscanf(in,"%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
        
        m = (y2-y1)/(x2-x1);
        if (m==M){
            fprintf(out, "%.2lf %.2lf %.2lf %.2lf\n",x1,y1,x2,y2);
            cont++;
        }
    }
    fclose(in);
    fclose(out);
    return cont;
}
