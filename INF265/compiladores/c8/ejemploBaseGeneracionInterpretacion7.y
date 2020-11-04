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
void imprimeTablaFunciones();
void generarCodigo(int op,int a1,int a2,int a3,int indice);
int genTemp();
int asignaTipoDato(int tipo, int posini, int posfin,int indice);

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
typedef struct{
	char nombre[80];
	double valor_retorno;
	int tipo;
	TipoTS tablaSimbolos[100];
	TipoTC TCodigo[100];
	int nSim;
	int cx;
	int nVarTemp;
}TipoFuncion;
TipoFuncion TablaFunciones[100];
int nFunc=0;
int nReg=0;
FILE* arch;
TipoTC TCodigo[100];
TipoTS tablaSimbolos[100];
/*variables*/
//int nSim=0;
//int cx=-1;
int nVarTemp=1;
char lexema[100];
%}
%token   NUMBER SI  IGUAL ENTONCES PARA  REPETIR ID SINO MIENTRAS ENTERO DECIMAL  MUESTRA
%token SUMAR SALTARF SALTAR ASIGNAR RESTAR MULTIPLICAR MAYOR IMPRIMIR MENOR LECTURA LEER PRINCIPAL
%token FUNCION PARAMETRO RETURN LLAMADAFUNCION ASIGNARRETORNO LLAMAR
%%
programa:  listadefinicionfuncion tipodato PRINCIPAL {nReg=nFunc;nFunc=1;$$=localizaSimbolo(lexema,FUNCION,0);} '(' ')' '{' listainst'}';
listadefinicionfuncion:listadefinicionfuncion definicionfuncion |definicionfuncion ;
definicionfuncion: tipodato ID  {nReg++;  nFunc++; $$=localizaSimbolo(lexema,FUNCION,nFunc);nFunc++;} '('  listaparams ')' '{' listainst retorno '}';
retorno: RETURN ID {$$=localizaSimbolo(lexema,RETURN,nFunc-1);} ';';
listaparams: listaparams ',' param| param ;
param: tipodato ID {$$=localizaSimbolo(lexema,PARAMETRO,nFunc-1);}   ;
llamadafuncion: ID {int i=localizaSimbolo(lexema,LLAMADAFUNCION,nFunc-1);$$=i;}'(' {$$=TablaFunciones[nFunc-1].cx;} listavalores {int i=genTemp();
 generarCodigo(ASIGNARRETORNO,i,$2 ,'-',nFunc-1);} ')' /*asignar el valor de retorno*/ {int i=genTemp();generarCodigo(LLAMAR,$2,'-','-',nFunc-1);}; 



listavalores: listavalores ',' expr {generarCodigo(ASIGNARPARAM,$3, '?','-',nFunc-1);} | expr {generarCodigo(ASIGNARPARAM,$1,'?','-',nFunc-1);} ;
listainst: listainst instr  | instr  ;
instr :  asignacion ';'   
	|selectiva  | iterativa | declaracion ';' | impresion ';' | lectura ';';
asignacion: ID {$$=localizaSimbolo(lexema,ID,nFunc-1);} IGUAL otroasig  {generarCodigo(ASIGNAR,$2,$4,'-',nFunc-1);} ;

otroasig: expr | llamadafuncion    ;


expr    : expr '+' term {int i=genTemp(); generarCodigo(SUMAR,i,$1,$3,nFunc-1);$$=i;};
expr    : expr '-' term  {int i=genTemp(); generarCodigo(RESTAR,i,$1,$3,nFunc-1) ;$$=i; };   
expr    :  term {$$=$1;}    ; 
term    : term '*' factor   {int i=genTemp(); generarCodigo(MULTIPLICAR,i,$1,$3,nFunc-1) ;$$=i; }
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
cond:    expr '<' expr  {int i=genTemp(); generarCodigo(MENOR,i,$1,$3,nFunc-1);$$=i;}
        |expr '>' expr {int i=genTemp(); generarCodigo(MAYOR,i,$1,$3,nFunc-1);$$=i;}
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
	int i=0,indice=0;
	printf("Tabla de código\n");
	for( indice;indice<nReg;indice++){
		printf("Indice %d\n",indice);
		for( i=0;i<=TablaFunciones[indice].cx;i++){
		printf("%d\t%d\t%d\t%d\n",TablaFunciones[indice].TCodigo[i].op,TablaFunciones[indice].TCodigo[i].a1,TablaFunciones[indice].TCodigo[i].a2,TablaFunciones[indice].TCodigo[i].a3);
	}}
}
int genTemp(){
	int pos;
	char t[10];
	sprintf(t,"_T%d",nVarTemp++);
	pos=localizaSimbolo(t,ID ,nFunc-1);
	return pos;
}
void generarCodigo(int op,int a1,int a2,int a3,int indice){
	TablaFunciones[indice].cx++;
	TablaFunciones[indice].TCodigo[TablaFunciones[indice].cx].op=op;
	TablaFunciones[indice].TCodigo[TablaFunciones[indice].cx].a1=a1;
	TablaFunciones[indice].TCodigo[TablaFunciones[indice].cx].a2=a2;
	TablaFunciones[indice].TCodigo[TablaFunciones[indice].cx].a3=a3;
	
}

int creacopia(int origen,int destino){
	 
	 
	TablaFunciones[destino].nVarTemp=TablaFunciones[origen].nVarTemp;
	TablaFunciones[destino].nSim=TablaFunciones[origen].nSim;
	TablaFunciones[destino].cx=TablaFunciones[origen].cx;
	TablaFunciones[destino].valor_retorno=TablaFunciones[origen].valor_retorno;
	TablaFunciones[destino].tipo=TablaFunciones[origen].tipo;
	 
	for(int i=0;i<=TablaFunciones[origen].cx;i++){
		TablaFunciones[destino].TCodigo[i].op=TablaFunciones[origen].TCodigo[i].op;
		TablaFunciones[destino].TCodigo[i].a1=TablaFunciones[origen].TCodigo[i].a1;
		TablaFunciones[destino].TCodigo[i].a2=TablaFunciones[origen].TCodigo[i].a2;
		TablaFunciones[destino].TCodigo[i].a3=TablaFunciones[origen].TCodigo[i].a3;

	}
	for(int i=0;i<=TablaFunciones[origen].nSim;i++){
		TablaFunciones[destino].tablaSimbolos[i].token=TablaFunciones[origen].tablaSimbolos[i].token;
		TablaFunciones[destino].tablaSimbolos[i].valor=TablaFunciones[origen].tablaSimbolos[i].valor;
strcpy(TablaFunciones[destino].tablaSimbolos[i].nombre,TablaFunciones[origen].tablaSimbolos[i].nombre);
	}
}


void interpretaCodigo(int indice){

       int i, a1,a2,a3,op;
       double d;
       for(i=0;i<=TablaFunciones[indice].cx;i++){
		op=TablaFunciones[indice].TCodigo[i].op;
		a1=TablaFunciones[indice].TCodigo[i].a1;
		a2=TablaFunciones[indice].TCodigo[i].a2;
		a3=TablaFunciones[indice].TCodigo[i].a3;	
		if (op==SUMAR) {
			TablaFunciones[indice].tablaSimbolos[a1].valor=TablaFunciones[indice].tablaSimbolos[a2].valor+TablaFunciones[indice].tablaSimbolos[a3].valor;
		}
		if (op==RESTAR) {
			TablaFunciones[indice].tablaSimbolos[a1].valor=TablaFunciones[indice].tablaSimbolos[a2].valor-TablaFunciones[indice].tablaSimbolos[a3].valor;
		}
		if (op==MULTIPLICAR) {
			TablaFunciones[indice].tablaSimbolos[a1].valor=TablaFunciones[indice].tablaSimbolos[a2].valor*TablaFunciones[indice].tablaSimbolos[a3].valor;
		}
		
		if (op==ASIGNAR) {
			TablaFunciones[indice].tablaSimbolos[a1].valor=TablaFunciones[indice].tablaSimbolos[a2].valor;
		}
		if (op==SALTAR) {
			i=a1-1;
		}
		if (op==MAYOR) {
			 TablaFunciones[indice].tablaSimbolos[a1].valor=TablaFunciones[indice].tablaSimbolos[a2].valor>TablaFunciones[indice].tablaSimbolos[a3].valor;
		
		}	
		if (op==MENOR) {
			 TablaFunciones[indice].tablaSimbolos[a1].valor=TablaFunciones[indice].tablaSimbolos[a2].valor<TablaFunciones[indice].tablaSimbolos[a3].valor;
		
		}	
		if (op==SALTARF) {
			if(!TablaFunciones[indice].tablaSimbolos[a1].valor) 
				i=a2-1;
		}
		if (op==IMPRIMIR) {
			printf("%.0lf\n",TablaFunciones[indice].tablaSimbolos[a1].valor) ;
				 
		}
		if (op==LEER){
			int valor;char ddd[30]; 
			scanf("%d",&valor); 	;
		}
		if (op==LLAMAR){
			interpretaCodigo(a1);
		}
		if(op==ASIGNARPARAM){
			TablaFunciones[a2].tablaSimbolos[a2]=TablaFunciones[indice].tablaSimbolos[a1].valor	;
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

int localizaSimbolo(char *nom,int token,int indice){

	int i;
	if(token==LLAMADAFUNCION ){
		for(i=0;i<nReg;i++){
			if(!strcmp(TablaFunciones[i].nombre,nom)){
				creacopia(i,nReg++);	
				return i;
			}
			
		}
		yyerror("Funcion indefinida");

	}
	else{
		for(i=0;i<TablaFunciones[indice].nSim;i++){
			if(!strcmp(TablaFunciones[indice].tablaSimbolos[i].nombre,nom)){/*if(!strcmp(tablaSimbolos[i].nombre,nom);*/
				if(token==RETURN){
					TablaFunciones[indice].valor_retorno=TablaFunciones[indice].tablaSimbolos[i].valor;
				}	
				return i;
			}
		}
		
		if(token==FUNCION){
			printf("en funcion"); 
			strcpy(TablaFunciones[indice].nombre,nom);
			TablaFunciones[indice].valor_retorno=0;
			TablaFunciones[indice].nSim=0;
			TablaFunciones[indice].cx=-1;
			TablaFunciones[indice].nVarTemp=0;
			return indice;
				
		}
		strcpy(TablaFunciones[indice].tablaSimbolos[TablaFunciones[indice].nSim].nombre,nom);
		TablaFunciones[indice].tablaSimbolos[TablaFunciones[indice].nSim].token=token;
		if(token==NUMBER){
			TablaFunciones[indice].tablaSimbolos[TablaFunciones[indice].nSim].valor=atof(lexema);
		}
		else{
			printf("Registra");
			TablaFunciones[indice].tablaSimbolos[TablaFunciones[indice].nSim].valor=0.0;
		}
		TablaFunciones[indice].nSim++;
		return TablaFunciones[indice].nSim-1;
	}

}


void imprimeTablaSimbolos(){
	int i,indice;
	printf("\nTabla de simbolos\n");
	for( indice=0;indice<=nReg+1;indice++){
		printf("Funcion: %sIndice %d retorno %lf \n",TablaFunciones[indice].nombre,indice,TablaFunciones[indice].valor_retorno);
		for(i=0;i<TablaFunciones[indice].nSim;i++){
			printf("%d %s %d %lf\n",i,TablaFunciones[indice].tablaSimbolos[i].nombre,TablaFunciones[indice].tablaSimbolos[i].token,TablaFunciones[indice].tablaSimbolos[i].valor);		
		}
}

}

void imprimeTablaFunciones(){
	for( int indice=0;indice<=nFunc;indice++){
		printf("Funcion Indice %d nombre %s \n",indice,TablaFunciones[indice].nombre);
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
		imprimeTablaFunciones();
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

