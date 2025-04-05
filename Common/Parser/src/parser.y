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
        $$ = new AST::Node(GRAMMERCONSTANTS::PROGRAM);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_GRAPH));
        $$->addChild($2);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_GRAPH));
        astTree = new AST::ASTTree($$);
    }
;

statements:
    /* empty */ {
        $$ = new AST::Node("statements");
    }
    | statements statement {
        $1->addChild($2);
        $$ = $1;
    }
;

statement:
    object_decl {
        $$ = new AST::Node(GRAMMERCONSTANTS::STATEMENT);
        $$->addChild($1);
    }
;

object_decl:
    SHAPE ID '{' property '}' {
        $$ = new AST::Node(GRAMMERCONSTANTS::OBJECT_DECL);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::SHAPE));
        $$->addChild(new AST::Node(*$1));
        delete $1;
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::ID));
        $$->addChild(new AST::Node(*$2));
        delete $2;
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_INTERNAL_BLOCK));
        $$->addChild($4);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_INTERNAL_BLOCK));
    }
;

property:
    PROPERTY_KEY '=' TEXT ';' {
        $$ = new AST::Node(GRAMMERCONSTANTS::PROPERTY);
        AST::Node* keyNode = new AST::Node(GRAMMERCONSTANTS::PROPERTY_KEY);
        keyNode->addChild(new AST::Node(*$1));
        $$->addChild(keyNode);
        delete $1;

        $$->addChild(new AST::Node("="));

        AST::Node* valueNode = new AST::Node(GRAMMERCONSTANTS::TEXT);
        valueNode->addChild(new AST::Node(*$3));
        $$->addChild(valueNode);
        delete $3;

        $$->addChild(new AST::Node(";"));
    }
    | PROPERTY_KEY '=' NUMBER ';' {
        $$ = new AST::Node(GRAMMERCONSTANTS::PROPERTY);
        AST::Node* keyNode = new AST::Node(GRAMMERCONSTANTS::PROPERTY_KEY);
        keyNode->addChild(new AST::Node(*$1));
        $$->addChild(keyNode);
        delete $1;

        $$->addChild(new AST::Node("="));

        AST::Node* valueNode = new AST::Node(GRAMMERCONSTANTS::NUMBER);
        valueNode->addChild(new AST::Node(*$3));
        $$->addChild(valueNode);
        delete $3;

        $$->addChild(new AST::Node(";"));
    }
;

%%
