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
%%

programa:  instr  ;   /*R3*/
instr :  asignacion ';'   /*R4*/   
	|selectiva   ; /*R9*/
asignacion: ID   IGUAL expr   ;   /*R10*/
expr    : expr '+' factor  ;  /*R11*/
expr    :  factor  ; /*R15*/
factor  : NUMBER   /*R16*/
        | ID    ; /*R18*/
cond:    expr '<' expr   ;    /*R28*/
selectiva:SI '(' cond ')'   '{' instr '}'  SINO '{' instr '}'   ; /*R33*/


%%
void yyerror(char *s){
	fprintf(stderr,"%s\n",s);
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
		printf("cadena válida\n"); 
	}
   
	else{
		printf("cadena inválida\n");	
	}
    }
}

