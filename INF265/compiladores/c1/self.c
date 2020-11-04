#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct{
	char nombre[60];
	int token;
	double valor;
}TipoTS;


TipoTS tablaSimb[100];
int nSim=0;
char lexema[60];

int  main(){
	char c;float t;
	int i;
	while(1) {
		c=getchar();
		if (c=='\n') continue;
        if (c == '/') {
            i = 0;
            lexema[i++] = c;
            c = getchar();
            if (c == '*') {
                while (1) {
                    lexema[i++] = c;
                    c = getchar();
                    if (lexema[i - 1] == '/' && lexema[i - 2] == '*') {
                        lexema[i] = 0;
                        ungetc(c, stdin);
                        printf("COMENTARIO");
                        break;
                    }
                }
            } else {
                ungetc(c, stdin);
            }
        }
		if (isdigit(c)){
			i=0;
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isdigit(c)||c=='.');
			ungetc(c,stdin);
			lexema[i]='\0';
			printf( "NUM");	
		}
		if (isalpha(c)){
			i=0;			
			do{
				lexema[i++]=c;
				c=getchar();
			}while(isalnum(c));
			ungetc(c,stdin);
			lexema[i]='\0';
            if (strcasecmp(lexema,"if")==0) 
				printf( "SI");
			else printf( "ID");
		}
		printf("%c",c);
	}
	return 0;
}

