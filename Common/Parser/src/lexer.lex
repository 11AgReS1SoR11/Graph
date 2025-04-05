%{
#include <stdio.h>
#include "parser.h"
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ;
[0-9]+          { yylval.num = atoi(yytext); return NUM; }
[ \t\r\n]         ;
.               { return *yytext; }

%%
