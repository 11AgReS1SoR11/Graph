%{

#include <stdio.h>

extern int yylineno;
extern char *yytext;

void yyerror(const char *s)
{
    fprintf(stderr, "Синтаксическая ошибка в строке %d, около '%.10s': %s\n",
            yylineno, yytext, s);
}

extern int yylex();

%}


%token NUM


%%

EVALUATE: EXPR  { printf("\n=%d\n", $1); } ;

EXPR:    TERM

        | EXPR '+' TERM { $$ = $1 + $3; }

        | EXPR '-' TERM { $$ = $1 - $3; }
;

TERM:    NUM

        | TERM '*' NUM  { $$ = $1 * $3; }

        | TERM '/' NUM  { $$ = $1 / $3; }
;

%%
