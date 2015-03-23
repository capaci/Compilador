
// Testar se funciona corretamente o empilhamento de parâmetros
// passados por valor ou por referência.


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
%token DIV AND NOT




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
              { /* insere última vars na tabela de símbolos */
				numVars++;
			 }
            | IDENT 
			  { /* insere vars na tabela de símbolos */
				numVars++;		
			 }
;

lista_idents: lista_idents VIRGULA IDENT  
            | IDENT
;

variavel: IDENT

/* -------------------------------------------------------------------
 *  COMANDOS
 * ------------------------------------------------------------------- */
comando_composto: T_BEGIN comandos T_END 
;

comandos: numero DOIS_PONTOS comando_sem_rotulo PONTO_E_VIRGULA
		| comando_sem_rotulo PONTO_E_VIRGULA
		| comandos
;

comando_sem_rotulo: atribuicao
					| chamada_de_procedimento
					| desvio
					| comando_composto
					| comando_condicional
					| comando_repetitivo
;

atribuicao: variavel ATRIBUICAO expressao
;
chamada_de_procedimento:;
desvio:;
comando_composto:;
comando_condicional:;
comando_repetitivo:;


/* -------------------------------------------------------------------
 *  EXPRESSOES
 * ------------------------------------------------------------------- */
expressao:	expressao_simples
		|	expressao_simples relacao expressao_simples
;

expressao_simples:	  expressao_simples MAIS termo  { geraCodigo(NULL, "SOMA"); }
					| expressao_simples MENOS termo { geraCodigo(NULL, "SUBT"); }
					| expressao_simples OR termo    { geraCodigo(NULL, "DISJ"); }
					| termo
;

termo:  termo MULT fator { geraCodigo(NULL, "MULT"); }
	|	termo AND fator  { geraCodigo(NULL, "CONJ"); }
	|	termo DIV fator  { geraCodigo(NULL, "DIVI"); }
	|	fator
;

fator:	IDENT
	|	ABRE_PARENTESES expressao_simples FECHA_PARENTESES
;

relacao:  > 
		| < 
		| >= 
		| <= 
		| =

numero:;

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
 *  Inicia a Tabela de Símbolos
 * ------------------------------------------------------------------- */

   yyin=fp;
   yyparse();

   return 0;
}

