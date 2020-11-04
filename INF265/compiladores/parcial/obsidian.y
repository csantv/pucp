%{
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
/*prototipos de funcion*/
void completarSaltosFSwitch(int pos,int ini,int fin);
int yylex();
void yyerror(char *s);
int localizaSimbolo(char *nom,int token,int decision);
void imprimeTablaSimbolos();
void imprimeTablaCodigo();
void generarCodigo(int op,int a1,int a2,int a3);
int genTemp();
int asignaTipoDato(int tipo, int posini, int posfin);
/*estructuras*/
typedef struct{
	char nombre[100];    
	int token; 
	int tipodato;/*number = 1,char = 2,str = 3, file = 4, date = 5, table = 6 */          
	double valor;        
}TipoTS;

typedef struct{
	int op;    
	int a1;
	int a2;
	int a3;
}TipoTC;

typedef struct{
	char palabra[100];	
}tablaCads;

tablaCads listaCads[100];

TipoTC TCodigo[100];
TipoTS tablaSimbolos[100];
/*variables*/
int nSim=0;
int cx=-1;
int nVarTemp=1;
int cantCads=0;
char lexema[100];
%}

%token NUMBER CARACTER CADENA ID ESIGUAL CONDICIONAL SINO PARA BUCLE DECREMENTO INCREMENTO DECLARAR SWITCH CASOSWITCH PORDEFECTO MIENTRAS MOSTRAR IMPLINEA IMPNOMBRE IMPTITULO IMPFECHA FORMATO_FECHA  IMPTABLA FINBUCLE
%token NUM CARAC STRING FIL DATE TABLE SALTARF SALTAR SUMAR RESTAR MULT FOR WHILE DECLARACION ASIGNACIONS COMPARACION SHOWT SELECTS SHOW SHOWL SHOWN SHOWTI SHOWD DECR INCR DISMINUIR SHOWA
%token MENOR MAYOR IGUAL MENIGUAL MAYIGUAL DIFERENTE INCREMENTAR SALTARCASEF SALTARCASE SALTLINEA MOSTEDAD AFECHA TODATE
%%

listainst:    listainst instr | instr ;

instr :         asignacion 
		| comparacion 
		| condition 
		| for 
		| decre 
		| incre 
		| switch
		| iterat 
		| show 
		| showLine 
		| showName
		| showTitle 
		| declaracion 
		| showDate
		| showAge
		| toDate
		;

tipoDato:     NUM {$$=1;} | CARAC {$$=2;} | STRING {$$=3;} | FIL {$$=4;} | DATE {$$=5;} | TABLE {$$=6;};

declaracion:  DECLARAR { $$=nSim;} listaDecl ':' tipoDato {$$=asignaTipoDato($5,$2,$3);} '#';

listaDecl:    listaDecl ',' ID {$$=localizaSimbolo(lexema,ID,0);}
              | ID {$$=localizaSimbolo(lexema,ID,0);} ;

asignacion:   ID {$$=localizaSimbolo(lexema,ID,1);} ':' paramAsign {generarCodigo(ASIGNACIONS,$2,$4,'-');} '#'
		
;

paramAsign:	expr {$$=$1;} | CADENA {$$=localizaSimbolo(lexema,CADENA,1);};

comparacion:  paramComp operador paramComp {int i=genTemp(); generarCodigo($2,i,$1,$3); $$=i;} ; 

paramComp:    ID {$$=localizaSimbolo(lexema,ID,1);}
              |expr {$$=$1;} ;
 
operador:      '<' 	{$$=MENOR;}
 	     | '>' 	{$$=MAYOR;}
             | ESIGUAL  {$$=IGUAL;}
             | '<' '='  {$$=MENIGUAL;}
             | '>' '='  {$$=MAYIGUAL;}
             | '!' '='  {$$=DIFERENTE;}
             ;

switch:      SWITCH {$$=cx+1;} ID {$$=localizaSimbolo(lexema,ID,1);} ':' listaCasosSwitch '#' {completarSaltosFSwitch($3,$2,cx);} ;

listaCasosSwitch: casoSwitch listaCasosSwitch | casoSwitch ;

casoSwitch: CASOSWITCH NUMBER {$$=localizaSimbolo(lexema,NUMBER,1);} {generarCodigo(SALTARCASEF,'-',$3,'-');$$=cx;} ':' listainst '#' {generarCodigo(SALTARCASE,'-','-','-');}{TCodigo[$4].a3=cx+1;} ;

decre:      DECREMENTO varRecD '#';

for:        PARA ID {$$=localizaSimbolo(lexema,ID,1);} {generarCodigo(SALTARF,$3,'?','-'); $$=cx;}  BUCLE ':' listainst '#' {generarCodigo(DISMINUIR,$3,'-','-');} {generarCodigo(SALTAR,$4,'-','-');} {TCodigo[$4].a2=cx+1;}  ;

show:       MOSTRAR ID {$$=localizaSimbolo(lexema,ID,1);} '#' {generarCodigo(SHOW,$3,ID,'-');}
	    | MOSTRAR CADENA {$$=localizaSimbolo(lexema,CADENA,1);} {generarCodigo(SHOW,$3,CADENA,'-');} '#'
	    | MOSTRAR SALTLINEA '#' {generarCodigo(SHOW,SALTLINEA,'-','-');} ;

showLine:   IMPLINEA CARACTER {$$=localizaSimbolo(lexema,CARACTER,1);} '#' {generarCodigo(SHOWL,$3,'-','-');}  ;

showName:   IMPNOMBRE CADENA {$$=localizaSimbolo(lexema,CADENA,1);} '#' {generarCodigo(SHOWN,$3,'-','-');} ;

showTitle:  IMPTITULO CADENA {$$=localizaSimbolo(lexema,CADENA,1);} '#' {generarCodigo(SHOWTI,$3,'-','-');} ;


showDate:   IMPFECHA ID {$$=localizaSimbolo(lexema,ID,1);} {generarCodigo(SHOWD,$3,'-','-');} '#';


showAge:    MOSTEDAD paramAge ',' paramAge '#' {generarCodigo(SHOWA,$2,$4,'-');} ; 

paramAge:   ID {$$=localizaSimbolo(lexema,ID,1);}
	    | NUMBER {$$=localizaSimbolo(lexema,NUMBER,1);} ;

toDate:	    AFECHA ID {$$=localizaSimbolo(lexema,ID,1);} ':' CADENA {$$=localizaSimbolo(lexema,CADENA,1);} '#' {generarCodigo(TODATE,$3,$6,'-');} ;

varRecD:    varRecD ',' ID {$$=localizaSimbolo(lexema,ID,1);} {generarCodigo(DISMINUIR,$4,'-','-');}
	    | ID {$$=localizaSimbolo(lexema,ID,1);} {generarCodigo(DISMINUIR,$2,'-','-');}; 

iterat:    MIENTRAS '('{$$=cx+1;} comparacion {generarCodigo(SALTARF,$4,'?','-');$$=cx;} ')' BUCLE ':' listainst '#' {generarCodigo(SALTAR,$3,'-','-');} {TCodigo[$5].a2=cx+1;}; 

condition:  CONDICIONAL '(' comparacion ')' {generarCodigo(SALTARF,$3,'?','-');$$=cx;} ':' listainst '#' {TCodigo[$5].a2=cx+1;}; 
            ;

incre:     INCREMENTO varRecI '#';

varRecI:    varRecI ',' ID {$$=localizaSimbolo(lexema,ID,1);} {generarCodigo(INCREMENTAR,$4,'-','-');}
	    | ID {$$=localizaSimbolo(lexema,ID,1);} {generarCodigo(INCREMENTAR,$2,'-','-');}; 

expr    : expr '+' term {int i=genTemp(); generarCodigo(SUMAR,i,$1,$3);$$=i;}; 
expr    : expr '-' term  {int j=genTemp(); generarCodigo(RESTAR,j,$1,$3);$$=j;};   
expr    : term    {$$ = $1;}   ;  
term    : term '*' factor {int w=genTemp(); generarCodigo(MULT,w,$1,$3);$$=w;}
        | factor {$$=$1;}
        ;
factor  : NUMBER {$$=localizaSimbolo(lexema,NUMBER,1);}
        | '(' expr ')'  {$$=$2;}
        ;
%%
void completarSaltosFSwitch(int pos,int ini,int fin){
	for(int i=ini;i<=fin;i++){
		if(TCodigo[i].op==SALTARCASE)TCodigo[i].a1=fin+1;	//Se utiliza SALTARCASE para no sobreescribir saltos de for o while
		else if(TCodigo[i].op==SALTARCASEF)TCodigo[i].a1=pos;
	}
}

void imprimeTablaCodigo(){
	int i=0,indice=0;
	char instr[40];
	printf("                     Tabla de Codigo\n");
	printf("===========================================================\n");
	printf("Pos Instruccion posTablaSimbolo    pos1ervalor   pos2dovalor\n");
	printf("-----------------------------------------------------------\n");
	for( i=0;i<=cx;i++){
		switch(TCodigo[i].op){	/*number = 1, char = 2, str = 3, file = 4, date = 5, table = 6, temp = 7*/ 
			case DECLARACION: strcpy(instr,"Declaracion"); break;
			case ASIGNACIONS: strcpy(instr,"Asignacion"); break;
			case MENOR: strcpy(instr,"Menor"); break;
			case MAYOR: strcpy(instr,"Mayor"); break;
			case IGUAL: strcpy(instr,"Igual"); break;
			case MENIGUAL: strcpy(instr,"MenorIgual"); break;
			case MAYIGUAL: strcpy(instr,"MayorIgual"); break;
			case DIFERENTE: strcpy(instr,"Diferente"); break;
			case SELECTS: strcpy(instr,"Select"); break;
			case SHOW: strcpy(instr,"Show"); break;
			case SHOWL: strcpy(instr,"ShowLine"); break;
			case SHOWN: strcpy(instr,"ShowName"); break;
			case SHOWTI: strcpy(instr,"ShowTitle"); break;
			case SHOWD: strcpy(instr,"ShowDate"); break;
			case MOSTEDAD: strcpy(instr,"ShowAge"); break;
			case TODATE: strcpy(instr,"ToDate"); break;
			case SHOWT: strcpy(instr,"ShowTable"); break;
			case INCREMENTAR: strcpy(instr,"Inc"); break;
			case DECR: strcpy(instr,"Dec"); break;
			case WHILE: strcpy(instr,"WhileLoop"); break;
			case FOR: strcpy(instr,"ForLoop"); break;
			case SALTAR: strcpy(instr,"Saltar"); break;	//Saltar siempre
			case SALTARF: strcpy(instr,"SaltarF"); break;	//Saltar si no cumple condicion
			case SUMAR: strcpy(instr,"Sumar"); break;
			case RESTAR: strcpy(instr,"Restar"); break;
			case MULT: strcpy(instr,"Producto"); break;     
			case DISMINUIR: strcpy(instr,"Disminuir"); break; 
			case SALTARCASEF: strcpy(instr,"SaltarCaseF"); break;
			case SALTARCASE: strcpy(instr,"SaltarCase"); break;
		}
		printf("%2d. %-15s %3d %16d %13d\n", i,instr, TCodigo[i].a1,TCodigo[i].a2,TCodigo[i].a3 );
	}
	printf("===========================================================\n");
}
int genTemp(){
	int pos;
	char t[10];
	sprintf(t,"_T%d",nVarTemp++);
	pos=localizaSimbolo(t,ID,0);
	tablaSimbolos[pos].tipodato=7;	//Variable de tipo temporal
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
       printf("%37s\n","CODIGO EJECUTADO");
       printf("===========================================================\n\n");
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
		if (op==MULT) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor*tablaSimbolos[a3].valor;
		}
		if (op==MAYOR) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor > tablaSimbolos[a3].valor;
		}
		if (op==MENOR) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor < tablaSimbolos[a3].valor;
				}
		if (op==IGUAL) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor == tablaSimbolos[a3].valor;
				}
		if (op==MENIGUAL) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor <= tablaSimbolos[a3].valor;
				}
		if (op==MAYIGUAL) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor >= tablaSimbolos[a3].valor;
				}
		if (op==DIFERENTE) {
			tablaSimbolos[a1].valor=tablaSimbolos[a2].valor != tablaSimbolos[a3].valor; 
		}
		if (op==SALTARF) {
			if(!tablaSimbolos[a1].valor) i = a2-1;	//Si es falso, debe saltar a la posicion dada
		}
		if (op==SALTAR) {
			i = a1-1;	//Siempre salta
		}
		if (op==DISMINUIR) {
			tablaSimbolos[a1].valor--;
		}
		if (op==INCREMENTAR) {
			tablaSimbolos[a1].valor++;
		}
		if(op==SHOW){
			if(a1==SALTLINEA)printf("\n");
			else if(a2==CADENA){
				for(int i=0;tablaSimbolos[a1].nombre[i];i++)if(tablaSimbolos[a1].nombre[i]!='"')printf("%c",tablaSimbolos[a1].nombre[i]);
				printf("\n");
			}
			else{
				if(tablaSimbolos[a1].tipodato != 3)printf("%.0lf\n",tablaSimbolos[a1].valor);
				else{ for(int i=1;listaCads[(int)(tablaSimbolos[a1].valor)].palabra[i]!='"';i++)printf("%c",listaCads[(int)(tablaSimbolos[a1].valor)].palabra[i]); printf("\n");}
			}
		}
		if(op==SHOWL){
			for(int i=0;i<59;i++)printf("%c",tablaSimbolos[a1].nombre[1]);
			printf("\n");
		}
		if(op==SHOWN){
			char ant=0;
			for(int i=0;tablaSimbolos[a1].nombre[i];i++){
				if(tablaSimbolos[a1].nombre[i]>='A' && tablaSimbolos[a1].nombre[i]<='Z' || tablaSimbolos[a1].nombre[i]>='a' && tablaSimbolos[a1].nombre[i]<='z'){	//Es letra
					if(ant=='"' || ant==' ')printf(" %c",tablaSimbolos[a1].nombre[i] - (tablaSimbolos[a1].nombre[i]>='a' && tablaSimbolos[a1].nombre[i]<='z')*('a'-'A'));
					else printf("%c",tablaSimbolos[a1].nombre[i] + (tablaSimbolos[a1].nombre[i]>='A' && tablaSimbolos[a1].nombre[i]<='Z')*('a'-'A'));
				}
				ant=tablaSimbolos[a1].nombre[i];		
			}
			printf("  ");
		}
		if(op==SHOWTI){
			for(int i=0;i<59;i++)printf("%c",'=');
			printf("\n");
			for(int i=0;i<40-strlen(tablaSimbolos[a1].nombre)-2;i++)printf(" ");
			for(int i=0;tablaSimbolos[a1].nombre[i];i++){
				if(tablaSimbolos[a1].nombre[i]!='"')printf("%c",tablaSimbolos[a1].nombre[i] - (tablaSimbolos[a1].nombre[i]>='a' && tablaSimbolos[a1].nombre[i]<='z')*('a'-'A'));
			}
			printf("\n");
			for(int i=0;i<59;i++)printf("%c",'=');
			printf("\n");
		}
		if(op==SHOWD){
			int fecha = (int)tablaSimbolos[a1].valor;
			int dd=fecha%100;
			int mm=(fecha%10000)/100;
			int aa=(fecha/10000);
			printf("%02d/%02d/%04d ",dd,mm,aa);
		}
		if(op==SHOWA){
			printf("%d años",((int)tablaSimbolos[a2].valor - (int)tablaSimbolos[a1].valor)/10000);		
		
		}	
		if(op==TODATE){
			char aux[20];
			int fecha=0,dato,i,j;
			for(i=1,j=0;tablaSimbolos[a2].nombre[i]!='/';i++,j++)aux[j]=tablaSimbolos[a2].nombre[i];
			aux[j]=0;
			fecha += atoi(aux);	    //Se uso el dia
			for(i=i+1,j=0;tablaSimbolos[a2].nombre[i]!='/';i++,j++)aux[j]=tablaSimbolos[a2].nombre[i];
			aux[j]=0;
			fecha += 100*atoi(aux);	    //Se uso el mes
			for(i=i+1,j=0;tablaSimbolos[a2].nombre[i];i++,j++)aux[j]=tablaSimbolos[a2].nombre[i];
			aux[j]=0;
			fecha += 10000*atoi(aux);   //Se uso el anio
			tablaSimbolos[a1].valor=fecha;	//Guardar en la variable la fecha
		}
		if(op==ASIGNACIONS){
			if(tablaSimbolos[a2].nombre[0]=='"'){strcpy(listaCads[cantCads++].palabra,tablaSimbolos[a2].nombre); tablaSimbolos[a1].valor=cantCads-1;}
			else tablaSimbolos[a1].valor = tablaSimbolos[a2].valor;
			
		}
		if (op==SALTARCASEF) {
			if(tablaSimbolos[a1].valor!=tablaSimbolos[a2].valor) i = a3-1;	//Si es falso, debe saltar a la posicion dada
		}
		if (op==SALTARCASE) {
			i = a1-1;	//Si es falso, debe saltar a la posicion dada
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

int localizaSimbolo(char *nom,int token,int decision){
	int i;
	for(i=0;i<nSim;i++){
		if(!strcasecmp(tablaSimbolos[i].nombre,nom)){/*if(!strcmp(tablaSimbolos[nSim].nombre,nom);*/
			if(token == ID && !decision){
				printf("ERROR: La variable %s ya ha sido previamente declarada\n",nom);
				exit(1);	
			}			
			return i;
		}
	}
	if(decision && token==ID){
		printf("ERROR: La variable %s no ha sido declarada\n",nom);	
		exit(1);
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
	int i;	char tipo[20];
    printf("===========================================================\n");
	printf("                     Tabla de simbolos\n");
    printf("===========================================================\n");
    printf("Pos  Nombre                   Token     Valor     TipoDato\n");
    printf("-----------------------------------------------------------\n");
	for(i=0;i<nSim;i++){
		switch(tablaSimbolos[i].tipodato){	/*number = 1, char = 2, str = 3, file = 4, date = 5, table = 6, temp = 7*/ 
			case 1: strcpy(tipo,"Number"); break;
			case 2: strcpy(tipo,"Char"); break;
			case 3: strcpy(tipo,"String"); break;
			case 4: strcpy(tipo,"File"); break;
			case 5: strcpy(tipo,"Date"); break;
			case 6: strcpy(tipo,"Table"); break;
			case 7: strcpy(tipo,"Temp"); break;
			default: strcpy(tipo,"Constant"); break;
		}		
		printf("%2d.  %-20s %8d  %8.0lf      %s\n",i,tablaSimbolos[i].nombre,tablaSimbolos[i].token,tablaSimbolos[i].valor,tipo);	
	}	
    printf("===========================================================\n");
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
	//Verificar que es palabra reservada
	if(!strcmp(lexema,"number"))   	return NUM;
	if(!strcmp(lexema,"char"))   	return CARAC;
	if(!strcmp(lexema,"str"))   	return STRING;
	if(!strcmp(lexema,"file"))   	return FIL;
	if(!strcmp(lexema,"date"))   	return DATE;
	if(!strcmp(lexema,"table"))   	return TABLE; 
        if(!strcmp(lexema,"equals"))    return ESIGUAL;
        if(!strcmp(lexema,"Condition")) return CONDICIONAL;
	if(!strcmp(lexema,"Else"))      return SINO;
        if(!strcmp(lexema,"For"))       return PARA;
        if(!strcmp(lexema,"Loop"))      return BUCLE;
        if(!strcmp(lexema,"Dec"))       return DECREMENTO;
        if(!strcmp(lexema,"Inc"))       return INCREMENTO;
        if(!strcmp(lexema,"Declare"))   return DECLARAR;
        if(!strcmp(lexema,"Select"))    return SWITCH;
        if(!strcmp(lexema,"Case"))      return CASOSWITCH;
        if(!strcmp(lexema,"Default"))   return PORDEFECTO;
        if(!strcmp(lexema,"While"))     return MIENTRAS;
        if(!strcmp(lexema,"show"))      return MOSTRAR;
        if(!strcmp(lexema,"showline"))  return IMPLINEA;
        if(!strcmp(lexema,"showname"))  return IMPNOMBRE;
        if(!strcmp(lexema,"showtitle")) return IMPTITULO;
        if(!strcmp(lexema,"showdate"))  return IMPFECHA;
        if(!strcmp(lexema,"Dateformat"))return FORMATO_FECHA; 
        if(!strcmp(lexema,"showage"))	return MOSTEDAD;
	if(!strcmp(lexema,"toDate"))	return AFECHA;
        if(!strcmp(lexema,"endl"))	return SALTLINEA;
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
		//Impresion de la tabla de simbolos y de codigo despues de terminar de analizar el codigo
		printf("Tabla de simbolos antes de interpretar\n");		
		imprimeTablaSimbolos();
		imprimeTablaCodigo();
		//Interpretar y ejecutar el codigo, finalmente imprimir la tabla de simbolos despues de modificar
		interpretaCodigo();
		printf("\n===========================================================\n");
		printf("Tabla de simbolos despues de interpretar\n");
		imprimeTablaSimbolos();
		for(int i=0;i<cantCads;i++)printf("%s\n",listaCads[i].palabra);
	}
	else{
		printf("cadena inválida\n");	
	}
}
