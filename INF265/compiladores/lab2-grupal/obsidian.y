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
%token NUMBER CARACTER CADENA ID TIPO ESIGUAL CONDICIONAL PARA BUCLE DECREMENTO INCREMENTO DECLARAR SWITCH CASOSWITCH PORDEFECTO MIENTRAS MOSTRAR IMPLINEA IMPNOMBRE IMPTITULO IMPFECHA FORMATO_FECHA  IMPTABLA FINBUCLE
%%

listainst:    listainst instr | instr ;

instr :       asignacion | comparacion | condition | for | decre | incre | switch | iterat | show | showLine | showName | showTitle | declaracion | showDate | createTable | showTable | cat | fin;

declaracion:  DECLARAR listaDecl ':' TIPO '#';

listaDecl:    ID {$$=localizaSimbolo(lexema,ID);} ',' listaDecl
              | ID {$$=localizaSimbolo(lexema,ID);} ;

asignacion:   listaDecl ':' listaExp '#';

listaExp:     expr ',' listaExp
              | expr ;

listaCads:    CADENA {$$=localizaSimbolo(lexema,CADENA);} ',' listaCads
              | CADENA {$$=localizaSimbolo(lexema,CADENA);};

comparacion:  paramComp operador paramComp;

paramComp:    ID {$$=localizaSimbolo(lexema,ID);}
              |expr
              |CARACTER {$$=localizaSimbolo(lexema,CARACTER);} ;

operador:     '<'|'>'|ESIGUAL|'<' '=' | '>' '=' | '!' '=';

switch:       SWITCH ID {$$=localizaSimbolo(lexema,ID);} ':' listaCasosSwitch '#' ;

listaCasosSwitch: listaCasosSwitch casoSwitch | casoSwitch ;

casoSwitch:  CASOSWITCH NUMBER {$$=localizaSimbolo(lexema,NUMBER);} ':' listainst '#' | PORDEFECTO ':' listainst '#' ;

show:        MOSTRAR varRecShow '#';

varRecShow:  paramShow ',' varRecShow | paramShow ;

showLine:   IMPLINEA CARACTER {$$=localizaSimbolo(lexema,CARACTER);} '#' ;

showName:   IMPNOMBRE listparamName '#';

showTitle:  IMPTITULO listparamName '#';

showDate:   IMPFECHA FORMATO_FECHA '(' ID {$$=localizaSimbolo(lexema,ID);}  ',' CADENA {$$=localizaSimbolo(lexema,CADENA);} ')' ;

createTable:    '<' ID {$$=localizaSimbolo(lexema,ID);} '>' ':' '(' '[' listaCads ']' ',' '[' listparamName ']' ')' ;

cat:        '$' ID {$$=localizaSimbolo(lexema,ID);} '$' ':' CADENA {$$=localizaSimbolo(lexema,CADENA);} '+' CADENA {$$=localizaSimbolo(lexema,CADENA);} ;

showTable:      IMPTABLA ID {$$=localizaSimbolo(lexema,ID);} '#' ;

listparamName: paramName ',' listparamName
               | paramName ;

paramName:     ID          {$$=localizaSimbolo(lexema,ID);}
               | CARACTER  {$$=localizaSimbolo(lexema,CARACTER);}
               | CADENA    {$$=localizaSimbolo(lexema,CADENA);} ;

paramShow:  CADENA      {$$=localizaSimbolo(lexema,CADENA);}
            |NUMBER     {$$=localizaSimbolo(lexema,NUMBER);}
            |ID         {$$=localizaSimbolo(lexema,ID);}
            |CARACTER   {$$=localizaSimbolo(lexema,CARACTER);};

decre:     DECREMENTO varRec '#';

incre:     INCREMENTO varRec '#';

fin:       FINBUCLE ;

varRec:    ID {$$=localizaSimbolo(lexema,ID);} ',' varRec | ID {$$=localizaSimbolo(lexema,ID);}; 

iterat:    MIENTRAS '(' comparacion ')' BUCLE ':' listainst '#' ; 

for:       PARA NUMBER {$$=localizaSimbolo(lexema,NUMBER);} BUCLE ':' listainst '#' ;

condition:  CONDICIONAL '(' comparacion ')' ':' listainst '#';

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
    else if(token==CADENA){
        tablaSimbolos[nSim].valor=strlen(lexema) - 2;   
    }
    else if(token==CARACTER){
        tablaSimbolos[nSim].valor=strlen(lexema) - 2;  
    }
	else{
		tablaSimbolos[nSim].valor=0.0;
	}
	nSim++;
	return nSim-1;
}

void imprimeTablaSimbolos(){
	int i;
    printf("==============================================\n");
	printf("                Tabla de simbolos\n");
    printf("==============================================\n");
    printf("Pos  Nombre                   Token     Valor\n");
    printf("----------------------------------------------\n");
	for(i=0;i<nSim;i++)
		printf("%2d.  %-20s %9d %10.4lf\n",i,tablaSimbolos[i].nombre,tablaSimbolos[i].token,tablaSimbolos[i].valor);		
    printf("==============================================\n");
}

int yylex(){
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
		if(!strcmp(lexema,"number")||!strcmp(lexema,"char")||!strcmp(lexema,"str")||!strcmp(lexema,"file")||!strcmp(lexema,"date")||!strcmp(lexema,"table")) return TIPO; 
        if(!strcmp(lexema,"equals"))   return ESIGUAL;
        if(!strcmp(lexema,"Condition"))return CONDICIONAL;
        if(!strcmp(lexema,"For"))      return PARA;
        if(!strcmp(lexema,"Loop"))     return BUCLE;
        if(!strcmp(lexema,"Dec"))      return DECREMENTO;
        if(!strcmp(lexema,"Inc"))      return INCREMENTO;
        if(!strcmp(lexema,"Declare"))  return DECLARAR;
        if(!strcmp(lexema,"Select"))   return SWITCH;
        if(!strcmp(lexema,"Case"))     return CASOSWITCH;
        if(!strcmp(lexema,"Default"))  return PORDEFECTO;
        if(!strcmp(lexema,"While"))    return MIENTRAS;
        if(!strcmp(lexema,"show"))     return MOSTRAR;
        if(!strcmp(lexema,"showline")) return IMPLINEA;
        if(!strcmp(lexema,"showname")) return IMPNOMBRE;
        if(!strcmp(lexema,"showtitle"))return IMPTITULO;
        if(!strcmp(lexema,"showdate"))return IMPFECHA;
        if(!strcmp(lexema,"Dateformat"))return FORMATO_FECHA; 
        if(!strcmp(lexema,"showtable"))return IMPTABLA;
        if(!strcmp(lexema,"Exit"))return FINBUCLE;

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
	}
	else{
		printf("cadena inválida\n");	
	}
}
