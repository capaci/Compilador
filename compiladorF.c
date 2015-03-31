
/* -------------------------------------------------------------------
 *            Aquivo: compilador.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Funções auxiliares ao compilador
 *
 * ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"


/* -------------------------------------------------------------------
 *  variáveis globais
 * ------------------------------------------------------------------- */

FILE* fp=NULL;
void geraCodigo (char* rot, char* comando ) {

  if (fp == NULL) {
    fp = fopen ("MEPA", "w");
  }

  if ( rot == NULL ) {
    fprintf(fp, "     %s\n", comando); fflush(fp);
  } else {
    fprintf(fp, "%s: %s \n", rot, comando); fflush(fp);
  }
}

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}

/* -------------------------------------------------------------------
 *  TABELA DE SIMBOLOS
 * ------------------------------------------------------------------- */
/* Inicia pilha de tipos */
void iniciaTipo () {
    pilhaTipo = malloc( sizeof (pilhaTp));
    pilhaTipo->topo = NULL;
    pilhaTipo->tam = 0;
}

/* Empilha tipo na pilha de tipos */
void empilhaTipo( char *tipoVar){
	char *tipo = malloc(sizeof(char) * TAM_TOKEN);

	strcpy(tipo,tipoVar);

	noTipo *no = malloc(sizeof(noTipo));

	no->tipo = tipo;
	
	no->anterior = pilhaTipo->topo;
	no->prox = NULL;

	if (pilhaTipo->tam != 0)
		pilhaTipo->topo->prox = no;
	pilhaTipo->topo = no;
	pilhaTipo->tam++;

	if (pilhaTipo->tam == 1)
		pilhaTipo->primeiro = pilhaTipo->topo;

}

/* Desempilha tipo da tabela de tipos*/
noTipo* desempilhaTipo(){
	if (pilhaTipo->tam == 0)
		return NULL;
	noTipo *no = pilhaTipo->topo;
	if (pilhaTipo->tam == 1)
		pilhaTipo->topo = NULL;
	else{
		pilhaTipo->topo = pilhaTipo->topo->anterior;
		pilhaTipo->topo->prox = NULL;
		no->anterior = NULL;
	}
	pilhaTipo->tam--;

	return no;
}

/* Imprime a pilha de Tipos*/
void imprimeTipo(){
	noTipo *no = pilhaTipo->primeiro;

	while(no != NULL){
		printf("id = %s\n", no->tipo);
		no = no->prox;
	}
}

/* -------------------------------------------------------------------
 *  TABELA DE SIMBOLOS
 * ------------------------------------------------------------------- */
/* Inicia pilha da tabela de simbolos */
void iniciaTS () {
    pilhaTS = malloc( sizeof (TS));
    pilhaTS->topo = NULL;
    pilhaTS->tam = 0;
}

/* Empilha simbolo na ts */
void empilhaTS( char *id, char *tpVar, char *cat, int nivelLex, int desloc){
	char *identificador = malloc(sizeof(char) * TAM_TOKEN);
	char *tipoVar = malloc(sizeof(char) * TAM_TOKEN);
	char *categoria = malloc(sizeof(char) * TAM_TOKEN);

	strcpy(identificador, id);
	strcpy(tipoVar, tpVar);
	strcpy(categoria, cat);

	noTS *no = malloc(sizeof(noTS));

	no->ident = identificador;
	no->tipo = tipoVar;
	no->categ = categoria;
	no->nivelLexico = nivelLex;
	no->deslocamento = desloc;
	no->anterior = pilhaTS->topo;
	no->prox = NULL;

	if (pilhaTS->tam != 0)
		pilhaTS->topo->prox = no;
	pilhaTS->topo = no;
	pilhaTS->tam++;

	if (pilhaTS->tam == 1)
		pilhaTS->primeiro = pilhaTS->topo;
}

/* Desempilha simbolo da ts*/
noTS* desempilhaTS(){
	puts("1");
	if (pilhaTS->tam == 0)
		return NULL;
	puts("2");

	noTS *no = pilhaTS->topo;
	puts("3");
	pilhaTS->topo = pilhaTS->topo->anterior;
	puts("4");
	pilhaTS->topo->prox = NULL;
	puts("5");
	no->anterior = NULL;
	puts("6");
	pilhaTS->tam--;

	return no;
}

/* Verifica se simbolo existe na TS*/
int buscaTS(char *simb, int nivelLex, int desloc){
	noTS *no = pilhaTS->topo;
	while (no != NULL){
		if (/*no->nivelLexico == nivelLex && no->deslocamento == desloc && */strcmp(simb, no->ident) == 0){
			noAux = no;
			return 1;
		}
		no = no->anterior;
	}

	return 0;
}

/* Imprime a TS*/
void imprimeTS(){
	noTS *no = pilhaTS->primeiro;

	while(no != NULL){
		printf("id = %s, tipo = %s, categ = %s, nivelLex = %d, desloc = %d\n", no->ident, no->tipo, no->categ, no->nivelLexico, no->deslocamento);
		no = no->prox;
	}
}

/* -------------------------------------------------------------------
 *  ROTULOS
 * ------------------------------------------------------------------- */
/* Gera um rótulo para a MEPA*/
char* geraRotulo(){
	printf("nada\n");
}

/* -------------------------------------------------------------------
 *  TIPOS
 * ------------------------------------------------------------------- */
/* Verificação de tipos*/
int verificaTipo(char *tipo){
	noTipo *a, *b;
	int retorno;
	a = desempilhaTipo();
	b = desempilhaTipo();

	if (strcmp(a->tipo,b->tipo) == 0 && strcmp(tipo, a->tipo) == 0)
		retorno = 1;
	else
		retorno = 0;

	empilhaTipo(a->tipo);
	free(a);
	free(b);
	return retorno;
}

void atualizaTipo(char *type, int num){
	noTS *no = pilhaTS->topo;	
	for (;num > 0; num --){
		strcpy(no->tipo, type);
		no = no->anterior;
	}
}

