#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.h"

void imprimeTablaCodigo()
{
    int i = 0, indice = 0;
    printf("Tabla de codigo\n");
    for (i = 0; i <= cx; i++) {
        printf("%d\t%d\t%d\t%d\n",
                TCodigo[i].op,
                TCodigo[i].a1,
                TCodigo[i].a2,
                TCodigo[i].a3);
    }
}

int genTemp()
{
    int pos;
    char t[10];
    sprintf(t, "_T%d", nVarTemp++);
    pos = localizaSimbolo(t, ID);
    return pos;
}

void generarCodigo(int op, int a1, int a2, int a3)
{
    cx++;
    TCodigo[cx].op = op;
    TCodigo[cx].a1 = a1;
    TCodigo[cx].a2 = a2;
    TCodigo[cx].a3 = a3;
}

void yyerror(char *s){
	fprintf(stderr,"%s\n",s);
}

int asignaTipoDato(int tipo, int ini, int fin)
{
    for (int i = ini; i <= fin; i++) {
        tablaSimbolos[i].tipodato = tipo;
    }
    return ini;
}

int localizaSimbolo(char *nom,int token){
	int i;
	for(i=0;i<nSim;i++){
		if(!strcmp(tablaSimbolos[i].nombre,nom)){/*if(!strcmp(tablaSimbolos[nSim].nombre,nom);*/
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
		printf("%d %s %d %lf %d\n",
                i,
                tablaSimbolos[i].nombre,
                tablaSimbolos[i].token,
                tablaSimbolos[i].valor,
                tablaSimbolos[i].tipodato);
	}

}

int yylex(){
	char c;int i;
	while((c=getchar())==' ');/*permitirme ignorar blancos*/
	/*if (c=='\n') return CAMBIOLINEA;*/
	if(isalpha(c)){
		i=0;
		do{
			lexema[i++]=c;
			c=getchar();
		}while(isalnum(c));
		ungetc(c,stdin);
		lexema[i++]='\0';
        if (!strcmp(lexema, "if")) return SI;
        if (!strcmp(lexema, "else")) return SINO;
        if (!strcmp(lexema, "while")) return MIENTRAS;
        if (!strcmp(lexema, "int")) return ENTERO;
        if (!strcmp(lexema, "double")) return DECIMAL;
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
    if (c == '=') return IGUAL;
	if(c=='\n'){
		return 0;
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
