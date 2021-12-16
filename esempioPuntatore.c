#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int funzioneACaso(char *);

int main(){
    char stringa[] = "pippo come stai";
    funzioneACaso(stringa);
}

int funzioneACaso(char *str){
    char *str2 = NULL;
    
    //str2 = str; //Copio in str2 il puntatore di str. OK, non da errore
    //*str2 = 'c';
    
    str2 = (char*)malloc(sizeof(char)*strlen(str));
    strcpy(str2,str);
    *str2 = 'c';
    printf("Str %s\nStr2 %s\n",str,str2);
    
    return 0;
}
