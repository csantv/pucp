%code {

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// prototipo de funciones
int yylex();
void yyerror(char *s);

int localizaSimbolo(char *nom,int token,int decision);
void imprimeTablaSimbolos();
void imprimeTablaCodigo();
void generarCodigo(int op,int a1,int a2,int a3);
int genTemp();
int asignaTipoDato(int tipo, int posini, int posfin);


// estructuras
typedef struct TipoTS TipoTS;
typedef struct TipoTC TipoTC;

struct TipoTS
{
	char nombre[100];    
	int token;
    /*number = 1,char = 2,str = 3, file = 4, date = 5, table = 6 */
	int tipodato;
	double valor;        
};

struct TipoTC
{
	int op;
	int a1;
	int a2;
	int a3;
};

TipoTC TCodigo[100];
TipoTS tablaSimbolos[100];

/*variables*/
int nSim=0;
int cx=-1;
int nVarTemp=1;
char lexema[100];

}

%token NUMBER CARACTER CADENA ID ESIGUAL CONDICIONAL SINO PARA BUCLE DECREMENTO INCREMENTO DECLARAR SWITCH CASOSWITCH PORDEFECTO MIENTRAS MOSTRAR IMPLINEA IMPNOMBRE IMPTITULO IMPFECHA FORMATO_FECHA  IMPTABLA FINBUCLE
%token NUM CARAC STRING FIL DATE TABLE SALTARF SALTAR SUMAR RESTAR MULT FOR WHILE DECLARACION ASIGNACIONS COMPARACION SHOWT SELECTS SHOW SHOWL SHOWN SHOWTI SHOWD CREATET CONCAT DECR INCR

%%

listainst:
    listainst instr
|   instr
;

instr :
    asignacion
|   comparacion
|   condition
|   for
|   decre
|   incre
|   switch
|   iterat
|   show
|   showLine
|   showName
|   showTitle
|   declaracion
|   showDate
|   createTable
|   showTable
|   cat
|   fin
;

tipoDato:
    NUM {$$=1;}
|   CARAC {$$=2;}
|   STRING {$$=3;}
|   FIL {$$=4;}
|   DATE {$$=5;}
|   TABLE {$$=6;}
;

declaracion:
    DECLARAR { $$=nSim;} listaDecl ':'
    tipoDato {$$=asignaTipoDato($5,$2,$3);}
    {int i=genTemp(); generarCodigo(DECLARACION,i,$2,$3);} '#'
;

listaDecl:
    listaDecl ',' ID {$$=localizaSimbolo(lexema,ID,0);}
|   ID {$$=localizaSimbolo(lexema,ID,0);}
;

listaAsign:
    listaAsign ',' ID {localizaSimbolo(lexema,ID,1);}
|   ID {$$=localizaSimbolo(lexema,ID,1);}
;

asignacion:
    listaAsign ':' listaExp
    {int i=genTemp(); generarCodigo(ASIGNACIONS,i,$1,$3);} '#'
;

listaExp:
    expr ',' listaExp {$$=$3;}
|   expr {$$=$1;};

listaCads:
    CADENA {$$=localizaSimbolo(lexema,CADENA,1);} ',' listaCads
|   CADENA {$$=localizaSimbolo(lexema,CADENA,1);};

comparacion:
    paramComp operador paramComp
    {int i=genTemp(); generarCodigo(COMPARACION,i,$1,$3); $$=$1;}
; 

paramComp:
    ID {$$=localizaSimbolo(lexema,ID,1);}
|   expr {$$=$1;}
|   CARACTER {$$=localizaSimbolo(lexema,CARACTER,1);}
;

operador:
    '<'
|   '>'
|   ESIGUAL
|   '<' '='
|   '>' '='
|   '!' '='
;

switch:
    SWITCH ID {$$=localizaSimbolo(lexema,ID,1);} ':' 
    listaCasosSwitch '#' 
    {int i=genTemp(); generarCodigo(SELECTS,i,$3,cx+1);}
;

listaCasosSwitch:
    listaCasosSwitch casoSwitch
|   casoSwitch
;

casoSwitch:
    CASOSWITCH NUMBER {$$=localizaSimbolo(lexema,NUMBER,1);} ':' listainst '#'
|   PORDEFECTO ':' listainst '#'
;

decre:
    DECREMENTO varRec '#' {int i=genTemp(); generarCodigo(DECR,i,cx,$2);}
;

for:
   PARA NUMBER {$$=localizaSimbolo(lexema,NUMBER,1);}
   {generarCodigo(SALTARF,$3,'?','-'); $$=cx;} 
   BUCLE ':' listainst '#'
   {TCodigo[$4].a2=cx+1;}
;

show:
    MOSTRAR varRecShow '#'
    {int i=genTemp(); generarCodigo(SHOW,i,cx,$2);}
;

varRecShow:
    paramShow ',' varRecShow {$$=$3;}
|   paramShow {$$=$1;}
;

showLine:
    IMPLINEA CARACTER {$$=localizaSimbolo(lexema,CARACTER,1);} '#'
    {int i=genTemp(); generarCodigo(SHOWL,i,$3,$3);}
;

showName:
    IMPNOMBRE listparamName '#'
    {int i=genTemp(); generarCodigo(SHOWN,i,cx,$2);}
;

showTitle:
    IMPTITULO listparamName '#'
    {int i=genTemp(); generarCodigo(SHOWTI,i,cx,$2);}
;

showDate:
    IMPFECHA FORMATO_FECHA '(' ID {$$=localizaSimbolo(lexema,ID,1);}  ','
    CADENA {$$=localizaSimbolo(lexema,CADENA,1);} ')'
    {int i=genTemp(); generarCodigo(SHOWD,i,$5,$8);}
;

createTable:
    '<' ID {$$=localizaSimbolo(lexema,ID,1);} '>' ':'
    '(' '[' listaCads ']' ',' '[' listparamName ']' ')'
    {int i=genTemp(); generarCodigo(CREATET,i,$3,$12);}
;
 
cat:
   '$' ID {$$=localizaSimbolo(lexema,ID,1);} '$' ':'
   CADENA {$$=localizaSimbolo(lexema,CADENA,1);} '+'
   CADENA {$$=localizaSimbolo(lexema,CADENA,1);}
   {int i=genTemp(); generarCodigo(CONCAT,i,$3,$10);}
;

showTable:
    IMPTABLA ID {$$=localizaSimbolo(lexema,ID,1);} '#'
    {int i=genTemp(); generarCodigo(SHOWT,i,$3,$3);}
;

listparamName:
    paramName ',' listparamName {$$=$3;}
|   paramName {$$=$1;}
;

paramName:
    ID        {$$=localizaSimbolo(lexema,ID,1);}
|   CARACTER  {$$=localizaSimbolo(lexema,CARACTER,1);}
|   CADENA    {$$=localizaSimbolo(lexema,CADENA,1);}
;

paramShow:
    CADENA     {$$=localizaSimbolo(lexema,CADENA,1);}
|   NUMBER     {$$=localizaSimbolo(lexema,NUMBER,1);}
|   ID         {$$=localizaSimbolo(lexema,ID,1);}
|   CARACTER   {$$=localizaSimbolo(lexema,CARACTER,1);}
;

fin:
    FINBUCLE
;

varRec:
    varRec ',' ID {$$=localizaSimbolo(lexema,ID,1);}
|   ID {$$=localizaSimbolo(lexema,ID,1);}
;

iterat:
    MIENTRAS '(' comparacion {generarCodigo(SALTARF,$3,'?','-'); $$=cx;} ')'
    BUCLE ':' listainst '#' {TCodigo[$4].a2=cx+1;}
; 

condition:
    CONDICIONAL '(' comparacion ')' ':' listainst '#'
    {int i=genTemp(); generarCodigo(SALTARF,i,$3,cx+1);}
;

incre: 
    INCREMENTO varRec '#'
    {int i=genTemp(); generarCodigo(INCR,i,cx,$2);}
;

expr:
    expr '+' term {int i=genTemp(); generarCodigo(SUMAR,i,$1,$3);} {$$=$3;}
|   expr '-' term  {int j=genTemp(); generarCodigo(RESTAR,j,$1,$3);}
|   term    {$$ = $1;}
;

term:
    term '*' factor {int w=genTemp(); generarCodigo(MULT,w,$1,$3);} {$$ = $3;}
|   factor {$$=$1;}
;

factor:
    NUMBER {$$=localizaSimbolo(lexema,NUMBER,1);}
|   '(' expr ')'  {$$=$2;}
;

%%

// lookup table token -> instruccion
void get_instr(YYSTYPE type, char* str)
{
    typedef struct item_t {YYSTYPE type; const char* name;} item_t;
    item_t table[] = {
        { DECLARACION, "Declaracion" },
        { ASIGNACIONS, "Asignacion" },
        { COMPARACION, "Comparacion" },
        { SELECTS, "Select" },
        { SHOW, "Show" },
        { SHOWL, "ShowLine" },
	    { SHOWN, "ShowName" },
	    { SHOWTI, "ShowTitle" },
		{ SHOWD, "ShowDate" },
        { CREATET, "CreateTable" },
	    { CONCAT, "Cat" },
		{ SHOWT, "ShowTable" },
        { INCR, "Inc" },
        { DECR, "Dec" },
	    { WHILE, "WhileLoop" },
		{ FOR, "ForLoop" },
        { SALTARF, "Condicion" },
        { SUMAR, "Sumar" },
        { RESTAR, "Restar" },
	    { MULT, "Producto" },
        { -1, NULL }
    };
    for (item_t* p = table; p->type != -1; ++p) {
        if (p->type == type) {
            strcpy(str, p->name);
        }
    }
}

void get_type(int type, char* str)
{ 
    typedef struct item_t {YYSTYPE type; const char* name;} item_t;
    item_t table[] = {
        { 1, "Number" },
        { 2, "Char" },
        { 3, "String" },
        { 4, "File" },
        { 5, "Date" },
        { 6, "Table" },
        { 7, "Temp" },
        { -1, NULL }
    };
    // por default Constant
    strcpy(str, "Constant");
    for (item_t* p = table; p->type != -1; ++p) {
        if (p->type == type) {
            strcpy(str, p->name);
        }
    }
}

int get_palabra_reserv(const char* str)
{
    typedef struct item_t {const char* name; YYSTYPE type; } item_t;
    item_t table[] = {
        { "number", NUM },
        { "char", CARAC },
        { "str", STRING },
        { "file", FIL },
        { "date", DATE },
        { "table", TABLE },
        { "equals", ESIGUAL },
        { "Condition", CONDICIONAL },
        { "Else", SINO },
        { "For", PARA },
        { "Loop", BUCLE },
        { "Dec", DECREMENTO },
        { "Inc", INCREMENTO },
        { "Declare", DECLARAR },
        { "Select", SWITCH },
        { "Case", CASOSWITCH },
        { "Default", PORDEFECTO },
        { "While", MIENTRAS },
        { "show", MOSTRAR },
        { "showline", IMPLINEA },
        { "showname", IMPNOMBRE },
        { "showtitle", IMPTITULO },
        { "showdate", IMPFECHA },
        { "showtable", IMPTABLA },
        { "Dateformat", FORMATO_FECHA },
        { "Exit", FINBUCLE },
        { NULL, -1 }
    };
    int res = -1;
    for (item_t *p = table; p->type != -1; ++p) {
        if (!strcmp(str, p->name)) {
            res = p->type;
        }
    }
    return res;
}

void imprimeTablaCodigo()
{
	int i=0,indice=0;
	char instr[40];
	printf("                     Tabla de Codigo\n");
	printf("===========================================================\n");
	printf("Pos Instruccion posTablaSimbolo    pos1ervalor   pos2dovalor\n");
	printf("-----------------------------------------------------------\n");
	for( i=0;i<=cx;i++){
        get_instr(TCodigo[i].op, instr);
		printf("%2d. %-15s %3d %16d %13d\n",
            i,instr,
            TCodigo[i].a1,
            TCodigo[i].a2,
            TCodigo[i].a3);
	}
	printf("===========================================================\n");
}

int genTemp()
{
	int pos;
	char t[10];
	sprintf(t,"_T%d",nVarTemp++);
	pos=localizaSimbolo(t,ID,0);
	tablaSimbolos[pos].tipodato=7;	//Variable de tipo temporal
	return pos;
}
void generarCodigo(int op,int a1,int a2,int a3)
{
	cx++;
	TCodigo[cx].op=op;
	TCodigo[cx].a1=a1;
	TCodigo[cx].a2=a2;
	TCodigo[cx].a3=a3;	
}

void yyerror(char *s)
{
	fprintf(stderr,"%s\n",s);
}

int asignaTipoDato(int tipo, int posini, int posfin)
{
	for(int i=posini;i<=posfin;i++){
		tablaSimbolos[i].tipodato=tipo;
	}
	return posfin;
}

int localizaSimbolo(char *nom,int token,int decision)
{
	int i;
	for(i=0;i<nSim;i++){
		if(!strcasecmp(tablaSimbolos[i].nombre,nom)){/*if(!strcmp(tablaSimbolos[nSim].nombre,nom);*/
			if(token == ID && !decision){
				printf("ERROR: La variable %s ya ha sido previamente declarada\n",nom);
				exit(1);	
			}			
			return i;
		}
	}
	if(decision && token==ID){
		printf("ERROR: La variable %s no ha sido declarada\n",nom);	
		exit(1);
	}
	strcpy(tablaSimbolos[nSim].nombre,nom);
	tablaSimbolos[nSim].token=token;
    switch (token) {
        case NUMBER:
		    tablaSimbolos[nSim].valor=atof(lexema);
            break;
        case CADENA:
            tablaSimbolos[nSim].valor=strlen(lexema) - 2;
            break;
        case CARACTER:
            tablaSimbolos[nSim].valor=strlen(lexema) - 2;
            break;
        default:
		    tablaSimbolos[nSim].valor=0.0;
    }
	nSim++;
	return nSim-1;
}

void imprimeTablaSimbolos()
{
	int i;
    char tipo[20];
    printf("===========================================================\n");
	printf("                     Tabla de simbolos\n");
    printf("===========================================================\n");
    printf("Pos  Nombre                   Token     Valor    TipoDato\n");
    printf("-----------------------------------------------------------\n");
	for(i=0;i<nSim;i++){
        get_type(tablaSimbolos[i].tipodato, tipo);
		printf("%2d.  %-20s %8d  %10.4lf    %s\n",i,
            tablaSimbolos[i].nombre,
            tablaSimbolos[i].token,
            tablaSimbolos[i].valor,tipo);	
	}	
    printf("===========================================================\n");
}

int yylex()
{
	char c;int i;
    while(1){
        c=getchar();
        if(c!='\n' && c!=' ') break;
    }
    if(c==EOF)return 0;
	if(isalpha(c)){
		i=0;
		do{
			lexema[i++]=c;
			c=getchar();
		}while(isalnum(c));
		ungetc(c,stdin);
		lexema[i++]='\0';
        int res = get_palabra_reserv(lexema);
        if (res != -1) return res;
		return ID;
	}
	if(isdigit(c)){ 
		//scanf("%d",&yylval);
		i=0;
		do{
			lexema[i++]=c;
			c=getchar();
		}while(isdigit(c));
		ungetc(c,stdin);
		lexema[i++]='\0';
		return NUMBER;
	}

    if(c=='\''){
        i=0;
        do{
			lexema[i++]=c;
			c=getchar();
		}while(c!='\'');
        lexema[i++]='\'';
        lexema[i++]=0;
        return CARACTER;
    }
    
    if(c == 34){
        i=0;
        do{
			lexema[i++]=c;
			c=getchar();
		}while(c!=34);
        lexema[i++]=34;
        lexema[i++]=0;
        return CADENA;
    }    
    	
	return c;
}

int main(){
	if(!yyparse()){
		printf("cadena válida\n");
		imprimeTablaSimbolos();
		imprimeTablaCodigo();
	}
	else{
		printf("cadena inválida\n");	
	}
}
