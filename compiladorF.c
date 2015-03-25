
/* -------------------------------------------------------------------
 *            Aquivo: compilador.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Fun��es auxiliares ao compilador
 *
 * ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"


/* -------------------------------------------------------------------
 *  vari�veis globais
 * ------------------------------------------------------------------- */

FILE* fp=NULL;
void geraCodigo (char* rot, char* comando) {

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

	pilhaTS->topo = no;
	pilhaTS->tam++;

	imprimeTS();

}

/* Desempilha simbolo da ts*/
noTS* desempilhaTS(){
	if (pilhaTS->tam == 0)
		return NULL;

	noTS *no = pilhaTS->topo;
	pilhaTS->topo = pilhaTS->topo->anterior;
	pilhaTS->topo->prox = NULL;
	no->anterior = NULL;
	pilhaTS->tam--;

	return no;
}

/* Busca simbolo na TS*/
int buscaTS(char *simb, int nivelLex, int desloc){
	noTS *no = pilhaTS->topo;
	while (no != NULL){
		if (no->nivelLexico == nivelLex && no->deslocamento == desloc && strcmp(simb, no->ident) == 0)
			return 1;
		no = no->anterior;
	}

	return 0;
}

/* Imprime a TS*/
void imprimeTS(){
	noTS *no = pilhaTS->topo;
	while(no != NULL){
		printf("id = %s, tipo = %s, categ = %s, nivelLex = %d, desloc = %d\n", no->ident, no->tipo, no->categ, no->nivelLexico, no->deslocamento);
		no = no->anterior;
	}
}


