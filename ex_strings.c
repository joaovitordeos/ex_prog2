/* 
 * Exercicios da disciplina de Prog2 - Manipulacao de Strings
 * Autor: Joao Vitor de Oliveira Souza
 * 27/03/23
 * Os exercicios estao aqui: "https://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:strings"
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMSTR 200
#define NULL_CHAR 0
#define a_CHAR 97
#define z_CHAR 122
#define A_CHAR 65
#define Z_CHAR 90
#define ZERO_CHAR 48
#define NINE_CHAR 57
#define SPACE 32
#define OP_BRK 91
#define CL_BRK 93

/* Ex.1 Escreve a string s ao contrario. */
void rev(char *str){
    int i, tamStr;
    tamStr = strlen(str);

    for (i=tamStr-1; i >= 0 ;i--)
        printf("%c", str[i]);
    printf("\n");
}

/* Ex.2 calcula o tamanho da string. */
int strLen(char *str){
    int i;

    i = 0;
    while (str[i] != NULL_CHAR)
        i++;

    return i;
}

/* Ex.3 Verifica se a string eh minuscula. Retorna 1 se sim, 0 caso contrario. */
int verifUp(char c){
    if ( (c >= a_CHAR) && (c <= z_CHAR))
        return 1;
    return 0;
}

/* Ex.3 Converte os char minusculo de uma string em maiusculo. */
void strUp(char *str){
    int i;

    i = 0;
    while (str[i] != NULL_CHAR){
        if (verifUp(str[i]))
            str[i] -= 32;
        i++;
    }
}

/* Ex.3.1 Verifica se a string eh maiuscula. Retorna 1 se sim, 0 caso contrario. */
int verifLow(char c){
    if ( (c >= A_CHAR) && (c <= Z_CHAR))
        return 1;
    return 0;
}

/* Ex.3.1 Converte os char maiuscula de uma string em minuscula. */
void strLow(char *str){
    int i;

    i = 0;
    while (str[i] != NULL_CHAR){
        if (verifLow(str[i]))
            str[i] += 32;
        i++;
    }
}

/* Ex.5 "Arrasta" todos os char 1 posicao para tras de acordo com o indice indicado.
   Ex: Se o idc = 2 e a string = boate, entao, a string ficara assim = bote. */
void shiftLeftChar(char *str, int idc){
    int i, tamStr;

    tamStr = strLen(str);

    for (i=idc; i < tamStr ; i++)
        str[i] = str[i+1]; 
}

/* Arrasta todas os char para a direita "aumentando" o tamanho da string a partir de idc.
   Ex: Se idc = 2 e a string = boate, entao, a string fica assim = boaate.*/
void shiftRightChar(char *str, int idc){
    int i, tamStr;

    tamStr = strLen(str);

    for (i=tamStr+1; i > idc ; i--)
        str[i] = str[i-1]; 
}

/* Ex.5 Verifica se o caractere eh numerico. Retorna 1 se sim e 0 caso contrario. */
int verifNum(char c){
    if ((c >= ZERO_CHAR) && (c <= NINE_CHAR))
        return 1;
    return 0;
}

/* Ex.5 Verifica se o caractere eh alfanumerico. Retorna 1 se sim e 0 caso contrario. */
int verifAlfanum(char c){
    if (verifLow(c) || verifUp(c) || (c == SPACE) || verifNum(c))
        return 1;
    return 0;
}

/* Ex.5 Remove todos os char nao alfabeticos (e nao espacos) de uma string. */
void cleanStr(char *str){
    int i;
    
    i = 0;
    while (str[i] != NULL_CHAR){
        if (!verifLow(str[i]) && !verifUp(str[i]) && !(str[i] == SPACE))
            shiftLeftChar(str, i);
        i++;
    }
}

/* Ex.6 Remove sequencias repetidas de char em uma string. */
void rmDuplicateChar(char *str){
    int i;

    i=0;
    while (str[i] != NULL_CHAR){
        if (str[i] == str[i+1])
            shiftLeftChar(str, i);
        else 
            i++;
    }
}

/* Ex.7 Remove a sequencia '][' de uma string. */
void cleanInvalidBracketStr(char *str){
    int i, j;

    i=0;
    while (str[i] != NULL_CHAR){
        if ( (str[i] == CL_BRK) && (str[i+1] == OP_BRK))
            for (j=0; j < 2 ;j++)
                shiftLeftChar(str, i);
        i++;
    }
    
}

/* Ex.7 Coloca entre '[]' char que nao sejam alfanumericos. */
void markNonAlphanum(char *str){
    int i, j;

    i = 0;
    while (str[i] != NULL_CHAR){
        if ( verifAlfanum(str[i]) )
            i++;
        else {
            for (j=0; j < 2 ;j++)
                shiftRightChar(str, i);
            str[i] = OP_BRK;
            str[i+2] = CL_BRK;
            i += 3; 
        }
    }
    cleanInvalidBracketStr(str);
}

/* Ex.8 Verifica se ha a ocorrencia da str1 na str2 a partir do idc da str2.
   Retorna 1 se encontrar e 0 caso contrario. */
int verifOcorrencia(char *str1, char *str2, int idc){
    int i;

    i = 0;
    while ( (str1[i] != NULL_CHAR) && (str2[idc] != NULL_CHAR)){
        if ( str1[i] != str2[idc] )
            return 0;
        i++;
        idc++;
    }
    return 1;
}

/* Ex.8 Procura a string 'agulha' na string 'palheiro'. Retorna o indice da ocorrencia.
   Retorna -1 caso nao encontre e -2 em caso de erro (Ex: tamanho invalido). */
int busca(char *agulha, char *palheiro){
    int i, tamStr1, tamStr2;

    tamStr1 = strLen(agulha);
    tamStr2 = strLen(palheiro);

    if ( (tamStr1 > tamStr2) || (tamStr1 == 0) || (tamStr2 == 0))
        return -2;
    
    i = 0;
    while (palheiro[i] != NULL_CHAR){
        if (verifOcorrencia(agulha, palheiro, i))
            return i;
        i++;
    }
    return -1;
}

/* Ex.9 Minha versao da funcao 'strcpy()'. Copia a str1 na str2. */
char *minhaStrcpy(char *str1, char *str2){
    int i;

    i = 0;
    while (str1[i] != NULL_CHAR){
        str2[i] = str1[i];
        i++;
    }
    str2[i] = NULL_CHAR;

    return str2;
}

/* Ex.9 Minha versao da funcao 'strcat()'. Concatena as strings str1 e str2.
   Retorna um ponteiro para a string resultante. */
char *minhaStrcat(char *str1, char *str2){
    int i, tamStr1, tamStr2, tamNewStr;
    char *newStr;

    tamStr1 = strLen(str1);
    tamStr2 = strLen(str2);

    if ( !(newStr = malloc( sizeof(char) * (tamStr1 + tamStr2 ) ) )) 
        return NULL;

    i = 0;
    while (str1[i] != NULL_CHAR){
        newStr[i] = str1[i];
        i++;
    }

    i = 0;
    while (str2[i] != NULL_CHAR){
        newStr[tamStr1 + i] = str2[i];
        i++;
    }
    newStr[tamStr1 + i] = NULL_CHAR;
    
    return newStr;
}

/* Ex.10 Remove todos os espacos da string. */
void rmSpaceStr(char *str){
    int i;
     
    i = 0;
    while (str[i] != NULL_CHAR){
        if ( str[i] == SPACE)
            shiftLeftChar(str, i);
        else
            i++;
    }
}

/* Ex.10 Verifica se a str eh palindromo. Retorna 1 se sim e 0 se nao.*/
int auxPalindromo(char *str, int ini, int fim){
    if ( ini == fim )   // caso base para strings de tamanho impar
        return 1;
    if ( (str[ini] == str[fim]) && (ini + 1 == fim) )  // caso base para strings de tamanho par
        return 1;
    if ( str[ini] != str[fim] )
        return 0;
    
    return auxPalindromo(str, ini + 1, fim - 1);
}

/* Ex.10 Cria uma copia da str, removendo da copia os espacos e numeros e transformando todos os
   caracteres em maiusculo, em seguida chama uma funcao auxiliar para verificar de fato se a string
   eh palindromo. Retorna 1 se sim, 0 se nao e -1 em caso de falha. */
int palindromo(char *str){
    char *newStr, tamNewStr, result;
    int i; 
    
    if ( !(newStr = malloc( sizeof(char) * TAMSTR ) ) ) 
        return -1;
    minhaStrcpy(str, newStr);

    // Trata a copia da str
    cleanStr(newStr);
    rmSpaceStr(newStr);
    strUp(newStr);

    tamNewStr = strLen(newStr);
    result = auxPalindromo(newStr, 0, tamNewStr - 1);
    free(newStr);

    return result;
}



int main (int argc, char *argv[]){
    char *str, *str1, *newStr;

    str = malloc(sizeof(char)*TAMSTR);
    str1 = malloc(sizeof(char)*TAMSTR);
    newStr = malloc(sizeof(char)*TAMSTR);
    str = argv[1];
    str1 = argv[2];

    //rev(str);
    //printf("%d\n", strLen(str));
    //strUp(str);
    //printf("%s\n", str);
    //strLow(str);
    //printf("%s\n", str);
    //cleanStr(str);
    //printf("%s\n", str);
    //for (int i=0; i<50 ; i++){
    //    shiftRightChar(str, 2);
    //    printf("%s\n", str);
    //}
    //rmDuplicateChar(str);
    //printf("%s\n", str);
    //markNonAlphanum(str);
    //printf("%s\n", str);
    //printf("O resultado da busca foi %d\n", busca(str, str1));
    //minhaStrcpy(str, newStr);
    //printf("Copia = %s\n", newStr);
    //newStr = minhaStrcat(str, str1);
    //printf("Concatenate = %s\n", newStr);
    //if (palindromo(str))
    //    printf("A frase/palavra \"%s\" eh palindromo ^-^\n", str);
    //else
    //    printf("A frase/palavra \"%s\" nao eh palindromo :(\n", str);

    return 0;
}
