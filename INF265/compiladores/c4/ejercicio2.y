%{
#include<string.h>
#include<stdio.h>
#include<ctype.h>
typedef struct{
	char nombre[20];    
	int token;           
	double valor;        
}TipoTS;
TipoTS tablaSimbolos[100];
int nSim=0;
char lexema[20];
int yylex();
void yyerror(char *s);
int localizaSimbolo(char *nom,int token);
void imprimeTablaSimbolos();

%}
%token NUM IF ELSE PROG ID
%token WHILE IMPRIMIR 
%%
command :  listainstr;
listainstr: listainstr instr  ';' |instr ';';

instr: asigna;
asigna: ID {$$=localizaSimbolo(lexema,ID);} '=' expr  {printf("%d %d\n",$2,$4);};
expr    : expr '+' term {$$=$1+$3;}
        | expr '-' term {$$=$1-$3;}
        | term {$$=$1;};  
term    : term '*' factor {$$=$1*$3;}  
        | factor {$$=$1;};
factor  : NUM {$$=$1;}
        | '(' expr ')' {$$=$2;};
%%
void imprimeTablaSimbolos(){
	int i;
	printf("Tabla de simbolos\n");
	for(i=0;i<nSim;i++){
		printf("%d %s %d %lf\n",i,tablaSimbolos[i].nombre,tablaSimbolos[i].token,tablaSimbolos[i].valor);		
	}

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
	if(token==NUM){
		scanf(nom,"%lf",&tablaSimbolos[nSim].valor);
	}
	else{
		tablaSimbolos[nSim].valor=0.0;
	}
	nSim++;
	return nSim-1;


}



int main(){
	if(!yyparse()){
		printf("cadena válida\n");
		imprimeTablaSimbolos();
	}
	else{
		printf("cadena inválida");	
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
		return ID;

	}
	if(isdigit(c)){
		ungetc(c,stdin);
		scanf("%d",&yylval);
		return NUM;
	}
	if(c=='\n'){
		return 0;
	}
	return c;
}
void yyerror(char *s){
	fprintf(stderr,"%s\n",s);
}






