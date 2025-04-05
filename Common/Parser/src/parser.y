%code requires {
#include "AST.hpp"
}

%{
#include <cstdio>
#include <string>

#include "AST.hpp"

extern int yylineno;
extern char *yytext;

AST::ASTTree* astTree = nullptr;

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d near '%.10s': %s\n",
            yylineno, yytext, s);
}

extern int yylex();
%}

%union {
    int num;
    AST::Node* node;
}

%token <num> NUM
%type <node> EXPR TERM FACTOR

%%

input:
    /* empty */
    | input line
;

line:
    EXPR {
        astTree = new AST::ASTTree($1);
        printf("\nParsing successful!\n");
    }
    | '\n'
;

EXPR:
    TERM { $$ = $1; }
    | EXPR '+' TERM {
        $$ = new AST::Node("+");
        $$->addChild($1);
        $$->addChild($3);
    }
    | EXPR '-' TERM {
        $$ = new AST::Node("-");
        $$->addChild($1);
        $$->addChild($3);
    }
;

TERM:
    FACTOR { $$ = $1; }
    | TERM '*' FACTOR {
        $$ = new AST::Node("*");
        $$->addChild($1);
        $$->addChild($3);
    }
    | TERM '/' FACTOR {
        $$ = new AST::Node("/");
        $$->addChild($1);
        $$->addChild($3);
    }
;

FACTOR:
    NUM {
        $$ = new AST::Node(std::to_string($1));
    }
    | '(' EXPR ')' { $$ = $2; }
;

%%
