#include "parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int yylex(void)
{
    int c = getchar();
    /* skip white space */
    while (c == ' ' || c == '\t') c = getchar();
    /* process numbers */
    if (c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        if (scanf("%lf", &yylval) != 1) abort();
        return NUM;
    }
    if (c == EOF) return YYEOF;

    return c;
}

void yyerror(char const *s)
{
    fprintf(stderr, "%s\n", s);
}

int main(void)
{
    return yyparse();
}
