/* reverse polish notation calculator */

%{

#include <stdio.h>
#include <math.h>

int yylex(void);
void yyerror (char const*);

%}

/* Bison declarations */
%define api.value.type {double}
%token NUM
%left '-' '+'
%left '*' '/'
%precedence NEG     /* negation--unary minus */
%right '^'          /* exponentiation */

%% /* grammar rules and actions follow */

input:
  %empty
| input line
;

line:
    '\n'
|   exp '\n'    { printf("\t%.10g\n", $1); }
|   error '\n'  { yyerrok;                 }
;

exp:
    NUM
|   exp '+' exp         { $$ = $1 + $3;     }
|   exp '-' exp         { $$ = $1 - $3;     }
|   exp '*' exp         { $$ = $1 * $3;     }
|   exp '/' exp         { $$ = $1 / $3;     }
|   '-' exp %prec NEG   { $$ = -$2;         }
|   exp '^' exp         { $$ = pow($1, $3); }
|   '(' exp ')'         { $$ = $2;          }
;

/*
exp:
  NUM
| exp exp '+'   { $$ = $1 + $2;         }
| exp exp '-'   { $$ = $1 - $2;         }
| exp exp '*'   { $$ = $1 * $2;         }
| exp exp '/'   { $$ = $1 / $2;         }
| exp exp '^'   { $$ = pow ($1, $2);    }   /* exponentiation
| exp 'n'       { $$ = -$1;             }   /* unary minus
;*/

%%
