/* 
 * Exercicios da disciplina de Prog2 - Manipulacao de Strings
 * Autor: Joao Vitor de Oliveira Souza
 * 27/03/23
 * 2,7,9,10
 */

/* 
   1. (posPal) Faça um programa que leia pelo teclado um texto com pelo menos 20  palavras
   (cada palavra com pelo menos 5 caracteres) separadas por ESPAÇO. Em seguida o programa
   deve ler do usuário uma letra ou dígito e então mostrar a posição de todas as palavras
   no texto que começam com a letra ou dígito informados. Numere a posição das palavras a partir
   de 0 (zero). 
    

   2. (primPal) Usando o resultado do exercício anterior, faça um programa que leia pelo teclado
   um texto com pelo menos 20 palavras (cada palavra com pelo menos 5 caracteres) separadas por
   ESPAÇO. Em seguida o programa deve mostrar uma relação contendo em cada linha a primeira letra
   de uma palavra seguida da posição de todas as palavras que começam com aquela letra.  
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_MAX 25
#define TXT_MAX 500

#define NEW_LINE 10
#define NULL_CHR 0
#define SPACE 32

typedef struct lista {
    struct lista *prox;
    char *str;
} lista_t;




/* Inicia a lista de strings, retorna um ponteiro para o primeiro elemento da lista,
   Se falhar, retorna NULL. */
lista_t *inicia_lista(){
    lista_t *s;

    if ( !(s = malloc(sizeof(lista_t))) )
        return NULL;

    s->prox = NULL;
    s->str = NULL;

    return s;
}

/* Remove todos os elementos da fila, libera espaco e devolve NULL. */
lista_t *destroi_lista (lista_t *s){
	lista_t *prox, *ante;
	
	prox = s->prox;

	while (prox != NULL){
		ante = prox;
		prox = prox->prox;

		free(ante);
		ante = NULL;
	}
	free(s);

	return NULL;
}

/* Le*/

/* Le strings e as insere numa lista de strings. Cada string eh separada por espacos em branco. */
int le_strings(lista_t *s){
    char *txt, *str, c;
    int i, j, tamTxt;

    if ( !(txt = malloc(sizeof(char)*TXT_MAX)) )
        return 0;

    fgets(txt);
    txt[strcspn(txt, "\n")] = '\0';

    i = 0;
    c = txt[i];
    while (c != NULL_CHR){
        if ( !(str = malloc(sizeof(char)*STR_MAX)) )
            return 0;
        
        for (j=0;txt[i]!=SPACE; i++, j++)
            str[j] = txt[i];
        str[j++] = NULL_CHR; 
        
        
    }
    

}

int main (){
    lista_t *s; 

    s = inicia_lista();

    

    s = destroi_lista(s);

    return 0;
}
