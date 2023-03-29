/* 
 * Exercicios da disciplina de Prog2 - Manipulacao de Strings
 * Autor: Joao Vitor de Oliveira Souza
 * 27/03/23
 * 1,2,7,9,10
 *
 * 
 * 1. (posPal) Faça um programa que leia pelo teclado um texto com pelo menos 20  palavras
 * (cada palavra com pelo menos 5 caracteres) separadas por ESPAÇO. Em seguida o programa
 * deve ler do usuário uma letra ou dígito e então mostrar a posição de todas as palavras
 * no texto que começam com a letra ou dígito informados. Numere a posição das palavras a partir
 * de 0 (zero). 
 *   
 * 2. (primPal) Usando o resultado do exercício anterior, faça um programa que leia pelo teclado
 * um texto com pelo menos 20 palavras (cada palavra com pelo menos 5 caracteres) separadas por
 * ESPAÇO. Em seguida o programa deve mostrar uma relação contendo em cada linha a primeira letra
 * de uma palavra seguida da posição de todas as palavras que começam com aquela letra.  
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
lista_t *cria_no_lista(){
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

        free(ante->str);
		free(ante);
		ante = NULL;
	}
    free(s->str);
	free(s);

	return NULL;
}

/* Adiciona uma string a lista. */
int adiciona_str(lista_t *s, char *str){
    lista_t *prox, *ante, *l;

    // Se o ponteiro da str do primeiro no da lista for NULL, atribui a string a ele
    if (s->str == NULL){
        s->str = str;
        return 1;
    }

    if ( !(l = cria_no_lista()) )
        return 0;

    l->str = str;

    prox = s->prox;
    ante = s;

    while (prox != NULL){
        ante = prox;
        prox = prox->prox;
    }

    ante->prox = l;
    return 1;
}

/* Le strings e as insere numa lista de strings. Cada string eh separada por espacos em branco. */
int le_strings(lista_t *s){
    char *txt, *str, c;
    int i, j;

    if ( !(txt = malloc(sizeof(char)*TXT_MAX)) )
        return 0;

    fgets(txt, TXT_MAX, stdin);
    txt[strcspn(txt, "\n")] = '\0';

    i = 0;
    c = txt[i];

    if ( !(str = malloc(sizeof(char)*STR_MAX)) )
        return 0;

    while (c != NULL_CHR){
        for (j=0;txt[i]!=SPACE && txt[i]!=NULL_CHR; i++, j++)
            str[j] = txt[i];
    
        str[j++] = NULL_CHR; 
        
        adiciona_str(s, str);

        if ( txt[i]!= NULL_CHR )
            if ( !(str = malloc(sizeof(char)*STR_MAX)) )
                return 0;
    
        c = txt[i];
        i++;
    }
    free(txt);
    return 1;
}

/* Imprime a posicao das palavras que iniciam com o char 'c'. */
int busca_strings(lista_t *s, char c){
    lista_t *prox;
    int i;
    
    i = 0;

    prox = s->prox;
    if (s->str[0] == c)
        printf("%d ", i);
    i++;
    while (prox!=NULL_CHR){
        if (prox->str[0] == c)
            printf("%d ", i);
        prox = prox->prox;
        i++;
    }

    return 1;
}

int main (){
    lista_t *s, *prox; 
    char c;

    s = cria_no_lista();

    le_strings(s);

    //scanf("%c", &c);
    //busca_strings(s, c);


    while (prox != NULL)
    {
        /* code */
    }
    

    s = destroi_lista(s);

    return 0;
}
