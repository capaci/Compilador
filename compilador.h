/* -------------------------------------------------------------------
 *            Arquivo: compilaodr.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [15/03/2012, 08h:22m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, protótipos e vaiáveis globais do compilador
 *
 * ------------------------------------------------------------------- */

#define TAM_TOKEN 32

typedef enum simbolos { 
  simb_program, simb_var, simb_begin, simb_end, 
  simb_identificador, simb_numero,
  simb_ponto, simb_virgula, simb_ponto_e_virgula, simb_dois_pontos,
  simb_atribuicao, simb_abre_parenteses, simb_fecha_parenteses,
  simb_mais
, simb_menos
, simb_asterisco
, simb_barra
, simb_abre_colchetes
, simb_fecha_colchetes
, simb_label
, simb_type
, simb_array
, simb_of
, simb_procedure
, simb_function
, simb_goto
, simb_if
, simb_then
, simb_else
, simb_while
, simb_do
, simb_or
, simb_div
, simb_and
, simb_not
, simb_igual
, simb_diferente
, simb_maior
, simb_menor
, simb_nao
} simbolos;

typedef enum tipo { 
  INTEGER
, BOOLEAN
, UNKNOW 
} tipo;

/* -------------------------------------------------------------------
 * TABELA DE SIMBOLOS
 * ------------------------------------------------------------------- */
typedef struct noTS {
	char *ident;
	char *tipo;
	char *categ;
	int nivelLexico;
	int deslocamento;
	struct noTS *prox, *anterior;
} noTS;

typedef struct TS{
	noTS *topo, *primeiro;
	int tam;
} TS;

/* -------------------------------------------------------------------
 * TABELA DE SIMBOLOS
 * ------------------------------------------------------------------- */
typedef struct noTipo{
	char *tipo;
	struct noTipo *prox, *anterior;	
} noTipo;

typedef struct pilhaTp{
	noTipo *topo, *primeiro;
	int tam;
} pilhaTp;

/* -------------------------------------------------------------------
 * variáveis globais
 * ------------------------------------------------------------------- */

extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN];
extern int nivel_lexico;
extern int desloc;
extern int nl;
extern char *ultimoRotulo;

simbolos simbolo, relacao;
char token[TAM_TOKEN];

TS *pilhaTS;
noTS *noAux; //no para fazer a busca dos endereços lexicos
char varAux[TAM_TOKEN]; //string para guardar a variavel que vai ser buscada 
pilhaTp *pilhaTipo;
noTipo *noTp;

/* -------------------------------------------------------------------
 * variáveis globais
 * ------------------------------------------------------------------- */
void iniciaTS();
void empilhaTS( char *id, char *tpVar, char *cat, int nivelLex, int desloc);
noTS* desempilhaTS();
int buscaTS(char *simb, int nivelLex, int desloc);
void imprimeTS();
char* geraRotulo();
int verificaTipos(char *tipo);
void atualizaTipo(char *type, int num);

void iniciaTipo ();
void empilhaTipo( char *tipoVar);
noTipo* desempilhaTipo();
void imprimeTipo();




