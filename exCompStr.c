/* 
 * Exercicios Complementares da disciplina de Prog2 - Manipulacao de Strings
 * Autor: Joao Vitor de Oliveira Souza
 * 27/03/23
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMSTR 25
#define TAMTXT 1024
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

struct lista {
    struct lista *prox;
    char *str;
};

typedef struct lista lista_t;

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
int strToLista(lista_t *s, char *str){
    lista_t *prox, *ante, *l;

    // Se o ponteiro da str do primeiro no da lista for NULL, atribui a string a ele
    if (s->str == NULL){
        s->str = str;
        return 1;
    }

    // Adiciona novo no a lista
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

/* Aloca uma string e retorna um ponteiro para a mesma. Se falhar retorna NULL */
char *alocaStr(){
    char *str;
    if ( !(str = malloc(sizeof(char) * TAMSTR)) )
        return NULL;
    return str;
}

/* Extrai uma parte do texto iniciada no indice 'idc' como uma string (com o fim dessa string sendo
   considerado como espaco). Retorna o indice onde a string acaba no txt (onde foi encontrado o espaco). */
int extractStr(char *txt, char *str, int idc){
    int j;

    j = 0;
    while ( (txt[idc] != SPACE) && (txt[idc] != NULL_CHAR) ){   // Enquanto nao encontrar um espaco ou char nulo 
        str[j] = txt[idc];                                      // Continua inserindo os caracteres em str formando
        idc++;                                                  // uma nova string.
        j++;
    }
    str[j++] = NULL_CHAR;   // No final da string eh inserido um char nulo.
    
    return idc;
}

/* Adiciona cada string do texto em uma lista (considerando que cada str esta separada por espaco). */
int txtToList(lista_t *s, char *txt){
    char *str, c;
    int i, j;

    i = 0;
    c = txt[i];

    if ( !(str = alocaStr()) )
        return 0;

    while (c != NULL_CHAR){
        j = 0;

        i = extractStr(txt, str, i);          // Extrai a proxima string do texto
    
        strToLista(s, str);                   // Adiciona a string a lista

        if ( txt[i] != NULL_CHAR )            // Aloca uma nova string se nao for o fim do texto
            if ( !(str = alocaStr()) ) 
                return 0;
    
        c = txt[i];
        i++;
    }
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
    while (prox != NULL){
        if (prox->str[0] == c)
            printf("%d ", i);
        prox = prox->prox;
        i++;
    }
    printf("\n");

    return 1;
}

/* Para cada string de uma lista sera exibido a posicao de cada ocorrencia de outras strings com o
   mesmo caractere inicial. */
void imprimeRelacao(lista_t *l){
    lista_t *prox;
    char c;

    prox = l->prox;
    c = l->str[0];

    printf("%c: ", c);
    busca_strings(l, c);
    
    while (prox != NULL){
        c = prox->str[0];
        printf("%c: ", c);
        busca_strings(l, c);

        prox = prox->prox;
    }
}


int main(int argc, char *argv[]){
    lista_t *l;
    char *txt;

    if ( !(txt = malloc(sizeof(char) * TAMTXT)) )
        return 1;

    fgets(txt, TAMTXT, stdin);
    txt[strcspn(txt, "\n")] = '\0'; // Insere um caractere nulo no lugar da quebra de linha no final do texto

    l = cria_no_lista();

    txtToList(l, txt);
    imprimeRelacao(l);
    
    l = destroi_lista(l);
    free(txt);
    return 0;
}
