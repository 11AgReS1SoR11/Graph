%{
#include <cstdio>
#include <string>
#include <iostream>

#include "SemanticAnalyzer.hpp"
#include "AST.hpp"

extern int yylineno;
extern char *yytext;
AST::ASTTree* astTree = nullptr;

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d near '%.10s': %s\n", yylineno, yytext, s);
}

extern int yylex(void);
%}

%code requires {
#include "AST.hpp"
}

%union {
    std::string* str;
    AST::Node* node;
}

%token <str> START_GRAPH END_GRAPH
%token <str> SHAPE PROPERTY_KEY ID NUMBER TEXT
%type <node> program statements statement object_decl property

%%

program:
    START_GRAPH statements END_GRAPH {
        $$ = new AST::Node("Program");
        $$->addChild(new AST::Node("@startgraph"));
        $$->addChild($2);
        $$->addChild(new AST::Node("@endgraph"));
        astTree = new AST::ASTTree($$);
    }
;

statements:
    /* empty */ {
        $$ = new AST::Node("statements");  // Пустой узел
    }
    | statements statement {
        $1->addChild($2);
        $$ = $1;
    }
;

statement:
    object_decl {
        $$ = new AST::Node("statement");
        $$->addChild($1);
    }
;

object_decl:
    SHAPE ID '{' property '}' {
        $$ = new AST::Node("object_decl");
        $$->addChild(new AST::Node("SHAPE"));
        $$->addChild(new AST::Node(*$1));
        delete $1;
        $$->addChild(new AST::Node("ID"));
        $$->addChild(new AST::Node(*$2));
        delete $2;
        $$->addChild(new AST::Node("{"));
        $$->addChild($4);
        $$->addChild(new AST::Node("}"));
    }
;

property:
    PROPERTY_KEY '=' TEXT ';' {
        $$ = new AST::Node("property");
        $$->addChild(new AST::Node("PROPERTY_KEY"));
        $$->addChild(new AST::Node(*$1));
        delete $1;
        $$->addChild(new AST::Node("="));
        $$->addChild(new AST::Node("TEXT"));
        $$->addChild(new AST::Node(*$3));
        delete $3;
        $$->addChild(new AST::Node(";"));
    }
;

%%
