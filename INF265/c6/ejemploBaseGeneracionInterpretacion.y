%code{
TipoTC TCodigo[100];
TipoTS tablaSimbolos[100];
/*variables*/
int nSim=0;
int cx=-1;
int nVarTemp=1;
char lexema[100];
}

%code requires {
/*prototipos de funcion*/
int yylex();
void yyerror(char *s);
int localizaSimbolo(char *nom,int token);
void imprimeTablaSimbolos();
void interpretaCodigo();
void generarCodigo(int op,int a1,int a2,int a3);
int genTemp();
int asignaTipoDato(int tipo, int posini, int posfin);
/*estructuras*/
typedef struct{
	char nombre[100];    
	int token; 
	int tipodato;   /*int 1 , double 2 , string 3, funcion 4*/       
	double valor;        
}TipoTS;

typedef struct{
	int op;    
	int a1;
	int a2;
	int a3;
}TipoTC;

extern TipoTC TCodigo[100];
extern TipoTS tablaSimbolos[100];
/*variables*/
extern int nSim;
extern int cx;
extern int nVarTemp;
extern char lexema[100];
}

%token   NUMBER SI  IGUAL ENTONCES PARA  REPETIR ID SINO MIENTRAS ENTERO DECIMAL 
%token SUMAR SALTARF SALTAR ASIGNAR RESTAR MULTIPLICAR

%%
programa: /*cabeceras prototipos*/ listainst;
listainst: listainst instr  | instr  ;
instr :  asignacion ';'   
	|selectiva  | iterativa | declaracion ';' ;
asignacion: ID {$$=localizaSimbolo(lexema,ID);} IGUAL expr  {generarCodigo(ASIGNAR,$2,$4,'-');} ;

expr:
    expr '+' term
    {
        int i=genTemp();
        generarCodigo(SUMAR,i, $1, $3);
        $$ = i;
    }
|   expr '-' term 
    {
        int i = genTemp();
        generarCodigo(RESTAR,i, $1, $3);
        $$ = i;
    }
|   term
;

term:
    term '*' factor
    {
        int i = genTemp();
        generarCodigo(MULTIPLICAR, i, $1, $3);
        $$ = i;
    }
|   factor {$$=$1;}
;

factor:
    NUMBER {$$=localizaSimbolo(lexema,NUMBER);} 
|   '(' expr ')'  {$$=$2;}
;

tipodato: ENTERO {$$=1;} | DECIMAL {$$=2;};
declaracion: tipodato { $$=nSim;} listaidentificador {$$=asignaTipoDato($1,$2,$3);} ;
listaidentificador: listaidentificador ',' ID  {$$=localizaSimbolo(lexema,ID);}
                    | ID  {$$=localizaSimbolo(lexema,ID);} ;
cond:    expr '<' expr
        |expr '>' expr 
        |expr IGUAL IGUAL expr
	|expr '>' IGUAL expr;

bloque:  '{' listainst '}' | instr ';' ;


selectiva:
    SI '(' cond ')'
    {
        generarCodigo(SALTARF,$3,'?','-');
        $$=cx;
    }
    bloque {TCodigo[$5].a2=cx+1;}
    {
        generarCodigo(SALTAR,'?','-','-');
        $$=cx;
    }
    otro  {TCodigo[$8].a1=cx+1;}
;



otro:  SINO bloque |
	 ;
iterativa: MIENTRAS '('cond')' bloque;

%%
