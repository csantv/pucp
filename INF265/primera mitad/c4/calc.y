%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct{
	char nombre[20];    
	int token;           
	double valor;        
}TipoTS;
TipoTS tablaSimbolos[100];
char lexema[100];

int yylex();
void yyerror(char *s);
%}
%token NUMBER ID
%%
command : expr {printf("El resultado %d\n",$1);}
        ;
expr    : expr '+' term {$$=$1+$3;};
expr    : expr '-' term {$$=$1-$3;};
expr    : term  {$$=$1;};
 
term    : term '*' factor {$$=$1*$3;}
        | factor {$$=$1;};
        ;
factor  : NUMBER {$$=$1;}
        | '(' expr ')' {$$=$2;}
        ;
%%

void yyerror(char *s){
	fprintf(stderr,"%s\n",s);
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
		return NUMBER;
	}
	if(c=='\n'){
		return 0;
	}
	return c;
}

int main(){
    while (!yyparse()) { 
		printf("cadena válida\n");
    }

	printf("cadena inválida");

    return 0;
}
