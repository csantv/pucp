%{
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
/*prototipos de funcion*/
int yylex();
void yyerror(char *s);
int localizaSimbolo(char *nom,int token);
void imprimeTablaSimbolos();
/*estructuras*/
typedef struct{
	char nombre[100];    
	int token; 
	int tipodato;          
	double valor;        
}TipoTS;
TipoTS tablaSimbolos[100];
/*variables*/
int nSim=0;
char lexema[100];
%}
%token NUMBER ID  TIPO  DECLARAR
%%
listainst: listainst instr | instr ;
instr :  asignacion | declaracion  ;
asignacion: ID {$$=localizaSimbolo(lexema,ID);} '=' expr   {printf("El resultado %d\n",$4);printf("Pos en tabla %d\n",$2);};


declaracion:    Decl ',' declaracion
            |   Decl DECLARAR TIPO
            ;
Decl:           ID {$$=localizaSimbolo(lexema,ID);} expr  {printf("El resultado %d\n",$3);printf("Pos en tabla %d\n",$2);}
            |   ID {$$=localizaSimbolo(lexema,ID);}
            ;      

expr    : expr '+' term {$$=$1+$3;};
expr    : expr '-' term  {$$=$1-$3;}  ;   
expr    :  term     {$$=$1;}    ;  
term    : term '*' factor  {$$=$1*$3;}
        | factor {$$=$1;}
        ;
factor  : NUMBER {$$=localizaSimbolo(lexema,NUMBER);} {$$=$1;}
        | '(' expr ')'  {$$=$2;}
        ;
%%
void yyerror(char *s){
	fprintf(stderr,"%s\n",s);
}


int localizaSimbolo(char *nom,int token){
	int i;
	for(i=0;i<nSim;i++){
		if(!strcasecmp(tablaSimbolos[nSim].nombre,nom)){/*if(!strcmp(tablaSimbolos[nSim].nombre,nom);*/
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
		printf("%2d.  %-7s %4d %8.4lf\n",i,tablaSimbolos[i].nombre,tablaSimbolos[i].token,tablaSimbolos[i].valor);		
	}

}

int yylex(){
	char c;int i;
	while((c=getchar())==' ');/*permitirme ignorar blancos*/
	if(isalpha(c)){
		i=0;
		do{
			lexema[i++]=c;
			c=getchar();
		}while(isalnum(c));
		ungetc(c,stdin);
		lexema[i++]='\0';
		if(!strcmp(lexema,"number")||!strcmp(lexema,"char")||!strcmp(lexema,"str")||!strcmp(lexema,"file")||!strcmp(lexema,"date")||!strcmp(lexema,"table")) return TIPO; 
        if(!strcmp(lexema,"as")) return DECLARAR;
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
    
    if(c=='\n')return 0;
	return c;
}

int main(){
	if(!yyparse()){
		printf("cadena válida\n");
		imprimeTablaSimbolos();
	}
	else{
		printf("cadena inválida\n");	
	}
}
