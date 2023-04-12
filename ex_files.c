/* 
 * Exercicios da disciplina de Prog2 - Manipulacao de Arquivos em C
 * Autor: Joao Vitor de Oliveira Souza
 * 29/03/23
 * Os exercicios estao aqui: "https://wiki.inf.ufpr.br/maziero/doku.php?id=prog2:acesso_a_arquivos"
 */
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
    if ( (c >= 97 && c <= 122)) // se esta entre o intervalo de letras minuc. em ASCII
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
        c = fgetc(a1);
    }

    return 1;
}

/* Ex.4 Cria uma matriz de lin x col. */
char **cria_matriz_char(int lin, int col){
	char **c;
	int i;
	
	if ( !(c = (char **)malloc(sizeof(char *) * lin) ) )
		return NULL;
	
	for (i=0; i < lin ;i++)
		if ( !(c[i] = (char *)malloc(sizeof(char) * col )) )
			return NULL;

	return c;
}

/* Ex.4 Destoi libera a memoria de uma matriz e retorna NULL. */
char **libera_matriz(char **c, int lin){
	int i;

	for (i=0; i < lin ;i++)
		free(c[i]);
	
	free(c);
	return NULL;
}

/* Ex.4 Imprime matriz. */
void imprime_matriz(char **m, int lin, int col){
	int i, j;

	for (i=0; i < lin ;i++, printf("\n"))
		for (j=0; j < col ;j++)
			printf("%c", m[i][j]);
}

/* Ex.4 Tranforma um arquivo.txt em mapa em uma matriz e retorna
   um ponteiro para a mesma. */
char **cria_mapa(FILE *a){
	char line[MAX_LINE + 1], **mapa;
	int lin, col, i, j;
	
	// Extrai os inteiros que indentificam linha x  coluna da primeira linha
	fscanf(a, "%d %d", &lin, &col);
	mapa = cria_matriz_char(lin, col);

	i = 0;
	fgets(line, MAX_LINE, a);
	while (i < lin){
		fgets(line, MAX_LINE, a);
		for (j=0; j < col ;j++){
			mapa[i][j] = line[j];
		}
		
		i++;
	}

	rewind(a);
	return mapa;
}

int main (int argc, char *argv[]){
    int col, lin;
	FILE *arqIn;
	char **mapa;

    if ( !(arqIn = fopen("mapa.txt", "r")) )
		return 1;
    
	mapa = cria_mapa(arqIn);
	fscanf(arqIn, "%d %d", &lin, &col);
	
	imprime_matriz(mapa, lin, col);

	mapa = libera_matriz(mapa, lin);
    fclose(arqIn);
    return 0;
}
