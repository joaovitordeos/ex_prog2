/*
 * Exercicios da disciplina de Prog2 - Manipulacao de Strings
 * Autor: Joao Vitor de Oliveira Souza
 * 2,7,9,10
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200
#define FIM_LINHA '\0'
#define COLC_ABERTO 91
#define COLC_FECHADO 93

/* Funcao auxiliar da 'inverte_str'. */
int inverte_aux(char *s, int ini){
    if (s[ini] == FIM_LINHA)
        return 0;
    
    inverte_aux(s, ini + 1);
    putchar(s[ini]);
    return 1;
}

/* Ex.1 Imprime a string s ao contrario. */
int inverte_str(char *s){
    return inverte_aux(s, 0);
}

/* Ex.2 Retorna um inteiro com o valor do tamanho da string. */
int tam_str(char *s){
    int i;
    
    for (i=0; s[i]!=FIM_LINHA ; i++ );
    i--;
    
    return i;
}

/* Ex.3 Converte as letras minusculas em maiusculas de acordo com a tabela ASCII. */
int maiuscula_str(char *s){
    int i, proxChar;
   

    i = 0;
    proxChar = i + 1;
    while(s[proxChar]!=FIM_LINHA) {
        
        s[i] = s[i] - 32;
        
        proxChar++;
        i++;
    }
    
    return 0;
}

/* Ex.6 Verifica se o tipo do char eh uma letra, num. ou espaco.
   Retorna 1 se eh do grupo citado o 0 caso contrario. */
int verif_char(char c){
	/* Espacos */
	if (c == 32)
		return 1;
	/* Numeros */
	if (c <= 57 && c >= 48)
		return 1;
	/* Letras de A-Za-z */
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return 1;
	/* caso nao seja nenhum dos casos acima, retorna 0. */
	return 0;
}

/* Ex.7 'Abre' um espaco no indice indicado, passando todos char a um indice a frente. */
int expande_str(char *s, int idc, int rep){
	int i, j, tamStr;
	
	tamStr = tam_str(s);

    for (i=0;i<rep;i++){
        puts(s);
	    for (j=tamStr;j>idc;j--)
		    s[j] = s[j-1];
        idc++;
        tamStr++;
    }
    return 1;
}

/* Ex.7 Coloca em '[]' caracteres que não sejam letras, num. ou empacos. */
int acrescenta_colchetes(char *s){
	int i, tamStr;

	tamStr = tam_str(s);
	i = 0;

	while (i<tamStr){
		if (!verif_char(s[i])){
			expande_str(s, i, 3);
			s[i] = COLC_ABERTO;
            s[i+2] = COLC_FECHADO;
 			i+=2;
			tamStr+=3;
		}
        else	
		    i++;
	}
    return 1;
}

/* Ex.8 Verifica se ha ocorrencia de s1 apartir de ini em s2. */
int verifica_ocorrencia(char *s1, char *s2, int ini, int tamS1){
    int i, j;
    
    for (i=0, j=ini; i<tamS1 ; i++, j++){
        if ( (s2[j] == s1[i]) && (i == (tamS1-1)) )
            return 1;
        if (s2[j] != s1[i])
            return 0;
    }
    return 1;
}

/* Ex.8 Busca a primeira ocorrencia da string s1 na s2, retornando o indice 
   de inicio da ocorrencia. */
int busca_ocorrencia(char *s1, char *s2){
    int tamS1, tamS2, i;
    
    tamS1 = tam_str(s1);
    tamS2 = tam_str(s2);
    
    if (tamS1 == 0 || tamS2 == 0 )
        return -2;
    if (tamS1 > tamS2)
        return -1;
        
    for (i=0; i<tamS2 ; i++)
        if (s2[i] == s1[0])
            if (verifica_ocorrencia(s1, s2, i, tamS1))
                return i;
    return -1;
}

int main () {
    char *s1, *s2;
    s1 = malloc(sizeof(char)*MAX_SIZE);
    //s2 = malloc(sizeof(char)*MAX_SIZE);
		
    fgets(s1, MAX_SIZE, stdin);
    //fgets(s2, MAX_SIZE, stdin);
    
    //printf("\n%d\n", busca_ocorrencia(s1, s2));

    //inverte_str(textOriginal);
    //printf("\n%d", tam_str(textOriginal));
    
    //maiuscula_str(textOriginal);
    acrescenta_colchetes(s1);
	//acrescenta_colchetes(s2);
	puts(s1);
    printf("\n%d\n", tam_str(s1));
	//puts(s2);


    return 0;
}
