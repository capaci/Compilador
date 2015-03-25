
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

int numVars;
char dados[256];
%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES 
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO

%token MAIS MENOS MULT DIV ABRE_COLCHETES FECHA_COLCHETES LABEL
%token TYPE ARRAY OF GOTO IF THEN ELSE WHILE DO OR
%token AND NOT IGUAL DIFERENTE MAIOR MENOR NUMERO

%%
/* -------------------------------------------------------------------
 *  PROGRAM
 * ------------------------------------------------------------------- */
programa    :{ 
             geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT 
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
			 sprintf ( dados, "DMEM %d", numVars); geraCodigo(NULL, dados);
             geraCodigo (NULL, "PARA");
             }
;

/* -------------------------------------------------------------------
 *  DECLARACAO DE VARIAVEIS
 * ------------------------------------------------------------------- */
bloco       : 
              parte_declara_vars
              { 
              }

              comando_composto 
              ;

parte_declara_vars: parte_declara_vars PONTO_E_VIRGULA declara_vars
 			| 		VAR {numVars = 0;} declara_vars { sprintf ( dados, "AMEM %d", numVars); geraCodigo(NULL, dados);  }
;

declara_vars: declara_vars declara_var 
            | declara_var 
;

declara_var : { }
              lista_id_var DOIS_PONTOS 
              tipo 
              { /* AMEM */

	          }
              PONTO_E_VIRGULA
;

tipo        : IDENT
;

lista_id_var: lista_id_var VIRGULA IDENT 
              { /* insere �ltima vars na tabela de s�mbolos */
				empilhaTS( token, "integer", "VS", 0, 0);
	
				numVars++;
			 }
            | IDENT 
			  { /* insere vars na tabela de s�mbolos */
				empilhaTS( token, "integer", "VS", 0, 0);
				numVars++;		
			 }
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;

variavel: IDENT
;

/* -------------------------------------------------------------------
 *  COMANDOS
 * ------------------------------------------------------------------- */
comando_composto: T_BEGIN comandos T_END 
;

comandos: rotulo comando_sem_rotulo
		| comando_sem_rotulo

;

comando_sem_rotulo: atribuicao  PONTO_E_VIRGULA
//					| chamada_de_procedimento
//					| desvio
//					| comando_composto
//					| comando_condicional
					| comando_repetitivo
;

atribuicao: variavel ATRIBUICAO expressao { geraCodigo(NULL, "ARMZ 0,0");}
;

//chamada_de_procedimento:;
//desvio:;
//comando_condicional:;
comando_repetitivo: WHILE expressao DO comando_composto
;

rotulo: numero DOIS_PONTOS
;
/* -------------------------------------------------------------------
 *  EXPRESSOES
 * ------------------------------------------------------------------- */
expressao:	expressao_simples {printf("sss3\n");}
;

expressao_simples:	  expressao_simples MAIS termo  { geraCodigo(NULL, "SOMA"); }
					| expressao_simples MENOS termo { geraCodigo(NULL, "SUBT"); }
					| expressao_simples OR termo    { geraCodigo(NULL, "DISJ"); }
					| termo
					|	expressao_simples  {printf("1\n");} relacao_booleana {printf("2\n");} expressao_simples {printf("3\n");}
;

termo:  termo MULT fator { geraCodigo(NULL, "MULT"); }
	|	termo AND fator  { geraCodigo(NULL, "CONJ"); }
	|	termo DIV fator  { geraCodigo(NULL, "DIVI"); }
	|	fator
;

fator:	IDENT
	|	numero
	|	ABRE_PARENTESES expressao_simples FECHA_PARENTESES
;

relacao_booleana:  MAIOR 
		| MENOR
		| MAIOR IGUAL
		| MENOR IGUAL
		| IGUAL
;

numero: NUMERO { sprintf(dados, "CRCT %s",token); geraCodigo(NULL, dados);}
;

%%

main (int argc, char** argv) {
	FILE* fp;
	extern FILE* yyin;

	if (argc<2 || argc>2) {
		printf("usage compilador <arq>a %d\n", argc);
		return(-1);
	}

	fp=fopen (argv[1], "r");
	if (fp == NULL) {
		printf("usage compilador <arq>b\n");
		return(-1);
	}


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
	iniciaTS();
	yyin=fp;
	yyparse();

	return 0;
}

