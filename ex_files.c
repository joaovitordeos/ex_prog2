#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define NULL_CHAR '\0'

/* Ex.1 Retorna um inteiro representando o numero de caracteres do arquivo FILE. */
int num_caracteres(FILE *a){
    int numChar;
    char c;

    c = fgetc(a);
    for(numChar = 1; c != EOF; numChar++)
        c = fgetc(a);

    return numChar;
}

/* Ex.2 Converte uma string em float. */
float converte_str_flt(char *s){
    float num;
    int i;

    num = 0;
    for (i=0; s[i] != NULL_CHAR ; i++)
        num = num*10 + (s[i] - 48);

    return num;
}


/* Ex.2 Retorna a media do valor dos inteiros de cada linha do arquivo. */
float media_arqv(FILE *a){
    float media, acc; 
    char *s;
    int i; 

    if ( !(s = malloc(sizeof(char)*MAX_LINE)))
        return -666;

    i = 1;

    fgets(s, MAX_LINE, a);
    acc = converte_str_flt(s);
    while ( !feof(a) ){
        acc += converte_str_flt(s);
        puts(s);
        fgets(s, MAX_LINE, a);
        i++;
    }
    
    media = acc / i;

    free(s);
    return media;
}


int main (){
    float media;
    int numChar;
    FILE *a;

    if ( !(a = fopen("numeros", "r")) )
        return 1;
    

    numChar = num_caracteres(a);
    media = media_arqv(a);
    
    printf("Num de caracteres: %d\n", numChar);
    printf("media do val do arqv: %f\n", media);

    fclose(a);
    return 0;
}