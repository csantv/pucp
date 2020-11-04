%code {

#include <stdio.h>

TipoTS tablaSimbolos[100];
TipoTC TCodigo[100];
int nSim = 0;
int cx = -1;
int nVarTemp = 1;
char lexema[100];

}

%code requires {
/*prototipos de funcion*/
int yylex();
int genTemp();
void yyerror(char *s);
int localizaSimbolo(char *nom,int token);
int asignaTipoDato(int tipo, int ini, int fin);
void imprimeTablaSimbolos();
void generarCodigo(int op, int a1, int a2, int a3);
void imprimeTablaCodigo();

/*estructuras*/
typedef struct{
	char nombre[100];
	int token; 
	int tipodato;          
	double valor;        
} TipoTS;

typedef struct{
	int op;
    int a1;
    int a2;
    int a3;
} TipoTC;

extern TipoTS tablaSimbolos[100];
extern TipoTC TCodigo[100];
/*variables*/
extern int nSim;
extern int cx;
extern int nVarTemp;
extern char lexema[100];

}

%token NUMBER ID CAMBIOLINEA SI ENTONCES MIENTRAS REPETIR SINO ENTERO DECIMAL
%token SUMAR
%token IGUAL "="

%%

programa:
   listainst;

listainst:
    listainst instr
|   instr
;
instr:
    asignacion ';'
|   selectiva
|   iterativa
|   declaracion ';'
;
asignacion: ID {$$=localizaSimbolo(lexema,ID);} IGUAL expr {printf("El resultado %d\n",$4);printf("Pos en tabla %d\n",$2);};
expr    : expr '+' term
        {
            int i = genTemp();
            generarCodigo(SUMAR, i, $1, $3);
        };
expr    : expr '-' term  {$$=$1-$3;}  ;   
expr    :  term     {$$=$1;}    ;  
term    : term '*' factor  {$$=$1*$3;}
        | factor {$$=$1;}
        ;
factor  : NUMBER {$$=localizaSimbolo(lexema,NUMBER);}
        | '(' expr ')'  {$$=$2;}
        ;

tipodato:
    ENTERO      {$$=1;}
|   DECIMAL     {$$=2;}
;

declaracion:
    tipodato {$$=nSim;} listaidentificador     {asignaTipoDato($1, $2, $3);}
;

listaidentificador:
    listaidentificador ',' ID       {$$=localizaSimbolo(lexema, ID);}
|   ID                              {$$=localizaSimbolo(lexema, ID);}
;

cond:
    expr '<' expr
|   expr '>' expr
|   expr IGUAL IGUAL expr
;

bloque:
    '{' listainst '}'
|   instr ';'
;
      

selectiva:
    SI '(' cond ')' bloque otro
;
otro:
    SINO bloque
|   %empty
;

iterativa: MIENTRAS '(' cond ')' bloque;

%%
