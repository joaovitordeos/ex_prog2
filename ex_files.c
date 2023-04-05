#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define NULL_CHAR 0

/* Ex.1 Retorna um inteiro representando o numero de caracteres do arquivo FILE. */
int num_caracteres(FILE *a){
    int numChar, i;
    char c;

    numChar = 0;

    c = fgetc(a);
    for(i = 0; (c != EOF); i++){
        if (c != 10 )
            numChar++;
        c = fgetc(a);
    }

    return numChar;
}

///* Ex.2 Converte uma string em float. */
//float converte_str_flt(char *s){
//    float num;
//    int i;
//
//    num = 0;
//    for (i=0; s[i] != NULL_CHAR ; i++)
//        num = num*10 + (s[i] - 48);
//
//    return num;
//}
//
//
///* Ex.2 Retorna a media do valor dos inteiros de cada linha do arquivo. */
//float media_arqv(FILE *a){
//    float media, acc; 
//    char line[MAX_LINE+1];
//    int i; 
//
//
//    i = 1;
//    acc = 0;
//
//    fgets(line, MAX_LINE, a);
//    line[strcspn(line, "\n")] = 0;
//
//    acc += converte_str_flt(line);
//    while ( !feof(a) ){
//        printf("%s", line);
//        fgets(line, MAX_LINE, a);
//        line[strcspn(line, "\n")] = 0;
//        acc += converte_str_flt(line);
//        i++;
//    }
//    
//    media = acc / i;
//
//    return media;
//}

/* Ex.2(Corrigido) */
float media_arqv(FILE *a){
    float media, numLinha, acc, valAtual;

    numLinha = 0;
    acc = 0;

    numLinha +=  fscanf(a, "%f", &valAtual);
    acc += valAtual;
    while ( !feof(a) ){
        numLinha +=  fscanf(a, "%f", &valAtual);
        acc += valAtual;
    }

    media = acc/numLinha; 

    return media;
}

/* Verifica se o caractere eh minusculo. */
int verifica_char(char c){
    if ( (c >= 97 && c <= 122))
        return 1;
    return 0;
}


/* Ex.3 Transforma os caracteres minusculos em maiusculos do arquivo 'a1
   no arqvuivo 'a2'. */
int converte_txt_maiusc(FILE *a1, FILE *a2){
    char c;

    c = fgetc(a1);
    while ( c != EOF ){
        if ( verifica_char(c) )
            fputc(c-32, a2);
        else
            fputc(c, a2);
    }

    return 1;
}


int main (){
    float media;
    int numChar;
    FILE *arqIn;// *arqOut;

    if ( !(arqIn = fopen("numeros", "r")) )
        return 1;
    if ( !(arqOut = fopen("maiusc", "w")) )
        return 1;

    

    //numChar = num_caracteres(arqIn);
    //rewind(arqIn); // retorna o ponteiro da stream para o local inicial
    //media = media_arqv(arqIn);
    
    //printf("Num de caracteres: %d\n", numChar);
    //printf("media do val do arqv: %f\n", media);
    converte_txt_maiusc(arqIn, arqOut);

    fclose(arqIn);
    fclose(arqOut);
    return 0;
}
