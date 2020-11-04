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
FILE* arch;
TipoTC TCodigo[100];
TipoTS tablaSimbolos[100];
/*variables*/
int nSim=0;
int cx=-1;
int nVarTemp=1;
char lexema[100];
%}
%token   NUMBER SI  IGUAL ENTONCES PARA  REPETIR ID SINO MIENTRAS ENTERO DECIMAL  MUESTRA
%token SUMAR SALTARF SALTAR ASIGNAR RESTAR MULTIPLICAR MAYOR IMPRIMIR MENOR LECTURA LEER
%token IMPRIMIRNUM MIENTRASDO INCREMENTO
%%
programa: /*cabeceras prototipos*/ listainst;
listainst: listainst instr  | instr  ;
instr :  asignacion ';'
    | incremento ';'
	|selectiva  | iterativa | declaracion ';' | impresion ';' | lectura ';';

asignacion: ID {$$=localizaSimbolo(lexema,ID);} IGUAL tipoasignacion  {generarCodigo(ASIGNAR,$2,$4,'-');} ;
tipoasignacion:
    expr    {$$=$1;}
|   cond    {$$=$1;}
;

incremento:
    ID {$$=localizaSimbolo(lexema,ID);} '+' '+' {generarCodigo(INCREMENTO,$2,'-','-');} ;

expr    : expr '+' term {int i=genTemp(); generarCodigo(SUMAR,i,$1,$3);$$=i;};
expr    : expr '-' term  {int i=genTemp(); generarCodigo(RESTAR,i,$1,$3) ;$$=i; };   
expr    :  term {$$=$1;}    ; 
term    : term '*' factor   {int i=genTemp(); generarCodigo(MULTIPLICAR,i,$1,$3) ;$$=i; }
        | factor {$$=$1;}
        ;
factor  : NUMBER {$$=localizaSimbolo(lexema,NUMBER);} 
        | ID {$$=localizaSimbolo(lexema,ID);} 
        | '(' expr ')'  {$$=$2;}
        ;
impresion:
    MUESTRA ID {$$=localizaSimbolo(lexema, ID);}{generarCodigo(IMPRIMIR,$3,'-','-');}
|   MUESTRA NUMBER {$$=localizaSimbolo(lexema, NUMBER);} {generarCodigo(IMPRIMIR,$3,'-','-');}
;
tipodato: ENTERO {$$=1;} | DECIMAL {$$=2;};
declaracion: tipodato { $$=nSim;} listaidentificador {$$=asignaTipoDato($1,$2,$3);} ;
listaidentificador: listaidentificador ',' ID  {$$=localizaSimbolo(lexema,ID);}
                    | ID  {$$=localizaSimbolo(lexema,ID);} ;
cond:    expr '<' expr  {int i=genTemp(); generarCodigo(MENOR,i,$1,$3);$$=i;}
        |expr '>' expr {int i=genTemp(); generarCodigo(MAYOR,i,$1,$3);$$=i;}
        |expr IGUAL IGUAL expr
	|expr '>' IGUAL expr;

bloque:  '{' listainst '}' | instr ';' ;
lectura: LECTURA ID {$$=localizaSimbolo(lexema, ID);} {  generarCodigo(LEER,$3,'-','-'); };

selectiva:SI '(' cond ')' {  generarCodigo(SALTARF,$3,'?','-'); $$=cx; } bloque 
    { generarCodigo(SALTAR,'?','-','-'); $$=cx; }  {TCodigo[$5].a2=cx+1;}  otro  {TCodigo[$7].a1=cx+1;}  ;



otro:  SINO bloque |
	 ;
iterativa: MIENTRAS '('{$$=cx+1;}cond {  generarCodigo(SALTARF,$4,'?','-'); $$=cx; } ')' bloque {  generarCodigo(SALTAR,$3 ,'-','-');  }  {TCodigo[$5].a2=cx+1;} ;

%%
void imprimeTablaCodigo(){
	int i=0,indice=0;
	printf("Tabla de código\n");
	for( i=0;i<=cx;i++){
			printf("%d\t%d\t%d\t%d\n", TCodigo[i].op, TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3 );
	}
}
int genTemp(){
	int pos;
	char t[10];
	sprintf(t,"_T%d",nVarTemp++);
	pos=localizaSimbolo(t,ID );
	return pos;
}
void generarCodigo(int op,int a1,int a2,int a3){
	cx++;
	TCodigo[cx].op=op;
	TCodigo[cx].a1=a1;
	TCodigo[cx].a2=a2;
	TCodigo[cx].a3=a3;
	
}

void interpretaCodigo(){

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
		if (op==INCREMENTO) {
			tablaSimbolos[a1].valor++;
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
			scanf("%d",&valor);
            tablaSimbolos[a1].valor = valor;
		}
        }

}

void yyerror(char *s){
	fprintf(stderr,"%s\n",s);
}

int asignaTipoDato(int tipo, int posini, int posfin){
	
	for(int i=posini;i<=posfin;i++){
		tablaSimbolos[i].tipodato=tipo;
	}
	return posfin;
}

int localizaSimbolo(char *nom,int token){
	int i;
	for(i=0;i<nSim;i++){
		if(!strcmp(tablaSimbolos[i].nombre,nom)){/*if(!strcmp(tablaSimbolos[i].nombre,nom);*/
				return i;
		}
	}
	strcpy(tablaSimbolos[nSim].nombre,nom);
	tablaSimbolos[nSim].token=token;
	if(token==NUMBER){
		tablaSimbolos[nSim].valor=atof(lexema);
	}
	else{
		tablaSimbolos[nSim].valor=0.0;
	}
	nSim++;
	return nSim-1;


}

void imprimeTablaSimbolos(){
	int i;
	printf("Tabla de simbolos\n");
	for(i=0;i<nSim;i++){
		printf("%d %s %d %lf %d\n",i,tablaSimbolos[i].nombre,tablaSimbolos[i].token,tablaSimbolos[i].valor ,tablaSimbolos[i].tipodato);		
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
			if(!strcmp(lexema,"do")) return MIENTRASDO; 
			if(!strcmp(lexema,"while")) return MIENTRAS; 
			if(!strcmp(lexema,"int")) return ENTERO; 
			if(!strcmp(lexema,"double")) return DECIMAL; 
			if(!strcmp(lexema,"printf")) return MUESTRA; 
			if(!strcmp(lexema,"read")) return LECTURA; 

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
		//imprimeTablaSimbolos();
		//imprimeTablaCodigo();
fflush(stdin);		interpretaCodigo();
		//imprimeTablaSimbolos();
	}
   
	else{
		printf("cadena inválida\n");	
	}
    }
}

