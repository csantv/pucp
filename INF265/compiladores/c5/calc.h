
#ifndef CALC_H
#define CALC_H

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
} TipoTS;

extern TipoTS tablaSimbolos[100];
/*variables*/
extern int nSim;
extern char lexema[100];

#endif
