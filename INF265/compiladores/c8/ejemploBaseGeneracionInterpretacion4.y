%{
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h> 
#include<ctype.h>
#include <unistd.h>
/*prototipos de funcion*/
int yylex();
void yyerror(char *s);
int localizaSimbolo(char *nom,int token,int indice);
void imprimeTablaSimbolos();
void interpretaCodigo(int indice);
void generarCodigo(int op,int a1,int a2,int a3,int indice);
int genTemp(int indice);
int asignaTipoDato(int tipo, int posini, int posfin, int indice);

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

typedef struct {
	char nombre[80];
	double valor_retorno;
	int tipo;
	TipoTS tablaSimbolos[100];
	TipoTC TCodigo[100];
	int nSim;
	int cx;
	int nVarTemp;
} TipoFuncion;

TipoFuncion TablaFunciones[100];
int nFunc=0;
int nReg;

FILE* arch;
char lexema[100];
/*
TipoTC TCodigo[100];
TipoTS tablaSimbolos[100];*/
/*variables*/
/*int nSim=0;
int cx=-1;
int nVarTemp=1;
char lexema[100];*/
%}
%token   NUMBER SI  IGUAL ENTONCES PARA  REPETIR ID SINO MIENTRAS ENTERO DECIMAL  MUESTRA
%token SUMAR SALTARF SALTAR ASIGNAR RESTAR MULTIPLICAR MAYOR IMPRIMIR MENOR LECTURA LEER
%token PRINCIPAL FUNCION PARAMETRO RETURN
%%
programa:  listadefinicionfuncion tipodato PRINCIPAL {nReg=nFunc;nFunc=1;$$=localizaSimbolo(lexema,FUNCION,0);} '(' ')' '{' listainst'}';
listadefinicionfuncion:listadefinicionfuncion definicionfuncion |definicionfuncion ;
definicionfuncion: tipodato ID  {nReg++;  nFunc++; $$=localizaSimbolo(lexema,FUNCION,nFunc);nFunc++;} '(' listaparams ')' '{' listainst retorno'}';
retorno: RETURN ID ';' {$$=localizaSimbolo(lexema,RETURN,nFunc-1);} ;
listaparams: listaparams ',' param| param ;
param: tipodato ID {$$=localizaSimbolo(lexema,PARAMETRO,nFunc-1);}   ;
llamadafuncion: ID '(' listavalores ')' ';';
listavalores: listavalores expr | expr;

listainst: listainst instr  | instr  ;
instr :  asignacion ';'   
	|selectiva  | iterativa | declaracion ';' | impresion ';' | lectura ';';

asignacion: ID {$$=localizaSimbolo(lexema,ID,nFunc-1);} IGUAL otroasig  {generarCodigo(ASIGNAR,$2,$4,'-',nFunc-1);} ;
otroasig: expr | llamadafuncion;

expr    : expr '+' term {int i=genTemp(nFunc-1); generarCodigo(SUMAR,i,$1,$3,nFunc-1);$$=i;};
expr    : expr '-' term  {int i=genTemp(nFunc-1); generarCodigo(RESTAR,i,$1,$3,nFunc-1) ;$$=i; };   
expr    :  term {$$=$1;}    ; 
term    : term '*' factor   {int i=genTemp(nFunc-1); generarCodigo(MULTIPLICAR,i,$1,$3,nFunc-1) ;$$=i; }
        | factor {$$=$1;}
        ;
factor  : NUMBER {$$=localizaSimbolo(lexema,NUMBER,nFunc-1);} 
        | ID {$$=localizaSimbolo(lexema,ID,nFunc-1);} 
        | '(' expr ')'  {$$=$2;}
        ;
impresion: MUESTRA ID {generarCodigo(IMPRIMIR,$2,'-','-',nFunc-1);} ;
tipodato: ENTERO {$$=1;} | DECIMAL {$$=2;};
declaracion: tipodato { $$=TablaFunciones[nFunc-1].nSim;} listaidentificador {$$=asignaTipoDato($1,$2,$3,nFunc-1);} ;
listaidentificador: listaidentificador ',' ID  {$$=localizaSimbolo(lexema,ID,nFunc-1);}
                    | ID  {$$=localizaSimbolo(lexema,ID,nFunc-1);} ;
cond:    expr '<' expr  {int i=genTemp(nFunc-1); generarCodigo(MENOR,i,$1,$3,nFunc-1);$$=i;}
        |expr '>' expr {int i=genTemp(nFunc-1); generarCodigo(MAYOR,i,$1,$3,nFunc-1);$$=i;}
        |expr IGUAL IGUAL expr
	|expr '>' IGUAL expr;

bloque:  '{' listainst '}' | instr ';' ;
lectura: LECTURA {  generarCodigo(LEER,'-','-','-',nFunc-1);  };

selectiva:SI '(' cond ')' {  generarCodigo(SALTARF,$3,'?','-',nFunc-1); $$=TablaFunciones[nFunc-1].cx; } bloque 
    { generarCodigo(SALTAR,'?','-','-',nFunc-1); $$=TablaFunciones[nFunc-1].cx; }  {TablaFunciones[nFunc-1].TCodigo[$5].a2=TablaFunciones[nFunc-1].cx+1;}  otro  {TablaFunciones[nFunc-1].TCodigo[$7].a1=TablaFunciones[nFunc-1].cx+1;}  ;



otro:  SINO bloque |
	 ;
iterativa: MIENTRAS '('{$$=TablaFunciones[nFunc-1].cx+1;}cond {  generarCodigo(SALTARF,$4,'?','-',nFunc-1); $$=TablaFunciones[nFunc-1].cx; } ')' bloque {  generarCodigo(SALTAR,$3 ,'-','-',nFunc-1);  }  {TablaFunciones[nFunc-1].TCodigo[$5].a2=TablaFunciones[nFunc-1].cx+1;} ;

%%
void imprimeTablaCodigo(){
	printf("Tabla de código\n");
	for (int i = 0; i <= nReg; i++) {
		printf("Indice %d\n", i);
		TipoFuncion tf = TablaFunciones[i];
		for (int j = 0; j <= tf.cx; j++) {
			printf("%d\t%d\t%d\t%d\n", tf.TCodigo[j].op, tf.TCodigo[j].a1,tf.TCodigo[j].a2,tf.TCodigo[j].a3 );	
		}
	}
}

int genTemp(int indice){
	int pos;
	char t[10];
	sprintf(t,"_T%d",TablaFunciones[indice].nVarTemp++);
	pos=localizaSimbolo(t,ID,indice);
	return pos;
}
void generarCodigo(int op,int a1,int a2,int a3,int indice){
	TablaFunciones[indice].cx++;
	int cx = TablaFunciones[indice].cx;
	TablaFunciones[indice].TCodigo[cx].op=op;
	TablaFunciones[indice].TCodigo[cx].a1=a1;
	TablaFunciones[indice].TCodigo[cx].a2=a2;
	TablaFunciones[indice].TCodigo[cx].a3=a3;
	
}

void interpretaCodigo(int indice){
	TipoFuncion tf = TablaFunciones[indice];
	TipoTS* tablaSimbolos = tf.tablaSimbolos;
	TipoTC* TCodigo = tf.TCodigo;
	int cx = tf.cx;

       int i, a1,a2,a3,op;
       double d;
       for(i=0;i<=cx;i++){
		op=TCodigo[i].op;
		a1=TCodigo[i].a1;
		a2=TCodigo[i].a2;
		a3=TCodigo[i].a3;	
		if (op==SUMAR) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor+tablaSimbolos[a3].valor;
		}
		if (op==RESTAR) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor-tablaSimbolos[a3].valor;
		}
		if (op==MULTIPLICAR) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor*tablaSimbolos[a3].valor;
		}
		
		if (op==ASIGNAR) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor;
		}
		if (op==SALTAR) {
			i=a1-1;
		}
		if (op==MAYOR) {
			 tablaSimbolos[a1].valor=tablaSimbolos[a2].valor>tablaSimbolos[a3].valor;
		
		}	
		if (op==MENOR) {
			 tablaSimbolos[a1].valor=tablaSimbolos[a2].valor<tablaSimbolos[a3].valor;
		
		}	
		if (op==SALTARF) {
			if(!tablaSimbolos[a1].valor) 
				i=a2-1;
		}
		if (op==IMPRIMIR) {
			printf("%.0lf\n",tablaSimbolos[a1].valor) ;
				 
		}
		if (op==LEER){
			int valor;char ddd[30]; 
			scanf("%d",&valor); 	;
		}
        }

}

void yyerror(char *s){
	fprintf(stderr,"%s\n",s);
}

int asignaTipoDato(int tipo, int posini, int posfin, int indice){
	
	for(int i=posini;i<=posfin;i++){
		TablaFunciones[indice].tablaSimbolos[i].tipodato=tipo;
	}
	return posfin;
}

int localizaSimbolo(char *nom,int token, int indice){
	int i;
	for(i=0;i<TablaFunciones[indice].nSim;i++){
		if(!strcmp(TablaFunciones[indice].tablaSimbolos[i].nombre,nom)){/*if(!strcmp(tablaSimbolos[i].nombre,nom);*/
			if (token == RETURN) {
				TablaFunciones[indice].valor_retorno = TablaFunciones[indice].tablaSimbolos[i].valor;
			}
			return i;
		}
	}
	if (token == FUNCION) {
		strcpy(TablaFunciones[indice].nombre, nom);
		TablaFunciones[indice].nSim = 0;
		TablaFunciones[indice].cx=-1;
		TablaFunciones[indice].nVarTemp = 0;
		return indice;
	}
	int nSim = TablaFunciones[indice].nSim;
	strcpy(TablaFunciones[indice].tablaSimbolos[nSim].nombre,nom);
	TablaFunciones[indice].tablaSimbolos[nSim].token=token;
	if(token==NUMBER){
		TablaFunciones[indice].tablaSimbolos[nSim].valor=atof(lexema);
	}
	else{
		TablaFunciones[indice].tablaSimbolos[nSim].valor=0.0;
	}
	TablaFunciones[indice].nSim++;
	return TablaFunciones[indice].nSim-1;


}

void imprimeTablaSimbolos(){
	printf("Tabla de simbolos\n");
	for (int i = 0; i <= nReg; i++) {
		TipoFuncion tf = TablaFunciones[i];
		printf("Indice %d retorno %lf \n", i, tf.valor_retorno);
		for (int j = 0; j < tf.nSim; j++) {
			printf("%d %s %d %lf %d\n",i,tf.tablaSimbolos[j].nombre,tf.tablaSimbolos[j].token,tf.tablaSimbolos[j].valor ,tf.tablaSimbolos[j].tipodato);		
		}
	}
}

int yylex(){
    	char c;int i;
	 while (!feof(arch)){
	    	c=fgetc(arch);
	    	if (c=='\n') continue;
	    	if (c==EOF) return c; 
		if (isspace(c)) continue;
		if(isalpha(c)){
			i=0;
			do{
				lexema[i++]=c;
				c=fgetc(arch);
			}while(isalnum(c));
			ungetc(c,arch);
			lexema[i++]='\0';
			if(!strcmp(lexema,"if")) return SI; /*espalreservada*/
			if(!strcmp(lexema,"else")) return SINO; /*espalreservada*/
			if(!strcmp(lexema,"while")) return MIENTRAS; 
			if(!strcmp(lexema,"int")) return ENTERO; 
			if(!strcmp(lexema,"double")) return DECIMAL; 
			if(!strcmp(lexema,"printf")) return MUESTRA; 
			if(!strcmp(lexema,"read")) return LECTURA; 
			if(!strcmp(lexema,"main")) return PRINCIPAL; 
			if(!strcmp(lexema,"return")) return RETURN; 

			return ID;

		}
		if(isdigit(c)){ 
			//scanf("%d",&yylval);
			i=0;
			do{
				lexema[i++]=c;
				c=fgetc(arch);
			}while(isdigit(c));
			ungetc(c,arch);
			lexema[i++]='\0';
			return NUMBER;
		}
		
		if(c=='='){
			return IGUAL;
		}
		
		return c;
	}
}

int main (int argc ,char *argv[] ){
   
    if(argc!=2) {
        printf("Ha olvidado su nombre.\n");
        exit(1); 
    }
    else{
        arch=fopen(argv[1],"r");
        if(!yyparse()){
		//printf("cadena válida\n");
		imprimeTablaSimbolos();
		imprimeTablaCodigo();
fflush(stdin);		interpretaCodigo(0);
		imprimeTablaSimbolos();
	}
   
	else{
		printf("cadena inválida\n");	
	}
    }
}

