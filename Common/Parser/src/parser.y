%{
#include <cstdio>
#include <string>
#include <iostream>
#include <memory>

#include "SemanticAnalyzer.hpp"
#include "AST.hpp"

extern int yylineno;
extern char *yytext;
std::unique_ptr<AST::ASTTree> astTree = nullptr;

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
%token <str> SHAPE PROPERTY_KEY ID NUMBER TEXT ARROW NOTE GRAPH DOT_CLOUD
%type <node> program statements statement statement_core object_decl properties property relation note graph graph_contents dot_cloud dot_cloud_blocks dot_cloud_block


%%

program:
    START_GRAPH statements END_GRAPH {
        $$ = new AST::Node(GRAMMERCONSTANTS::PROGRAM);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_GRAPH));
        $$->addChild($2);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_GRAPH));
        astTree = std::make_unique<AST::ASTTree>($$);
    }
;

statements:
    /* empty */ {
        $$ = new AST::Node(GRAMMERCONSTANTS::STATEMENTS);
    }
    | statements statement {
        $1->addChild($2);
        $$ = $1;
    }
;

statement:
    statement_core {
        $$ = new AST::Node(GRAMMERCONSTANTS::STATEMENT);
        $$->addChild($1);
    }
    | statement_core ';' {
        $$ = new AST::Node(GRAMMERCONSTANTS::STATEMENT);
        $$->addChild($1);
        $$->addChild(new AST::Node(";"));
    }
;

statement_core:
    object_decl { $$ = $1; }
    | relation { $$ = $1; }
    | note { $$ = $1; }
    | graph { $$ = $1; }
    | dot_cloud { $$ = $1; }
;

graph:
    GRAPH ID '{' graph_contents '}' {
        $$ = new AST::Node(GRAMMERCONSTANTS::GRAPH);
        delete $1;

        AST::Node* id = new AST::Node(GRAMMERCONSTANTS::ID);
        id->addChild(new AST::Node(*$2));
        $$->addChild(id);
        delete $2;

        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_INTERNAL_BLOCK));
        $$->addChild($4);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_INTERNAL_BLOCK));
    }
    | GRAPH ID '(' properties ')' '{' graph_contents '}' {
        $$ = new AST::Node(GRAMMERCONSTANTS::GRAPH);
        delete $1;

        AST::Node* id = new AST::Node(GRAMMERCONSTANTS::ID);
        id->addChild(new AST::Node(*$2));
        $$->addChild(id);
        delete $2;

        $$->addChild(new AST::Node("("));
        $$->addChild($4);
        $$->addChild(new AST::Node(")"));

        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_INTERNAL_BLOCK));
        $$->addChild($7);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_INTERNAL_BLOCK));
    }
;

graph_contents:
    /* empty */ {
        $$ = new AST::Node(GRAMMERCONSTANTS::GRAPH_CONTENTS);
    }
    | graph_contents object_decl {
        $1->addChild($2);
        $$ = $1;
    }
    | graph_contents relation {
        $1->addChild($2);
        $$ = $1;
    }
;

dot_cloud:
    DOT_CLOUD ID '{' dot_cloud_blocks '}' {
        $$ = new AST::Node(GRAMMERCONSTANTS::DOT_CLOUD);
        delete $1;

        AST::Node* id = new AST::Node(GRAMMERCONSTANTS::ID);
        id->addChild(new AST::Node(*$2));
        $$->addChild(id);
        delete $2;

        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_INTERNAL_BLOCK));
        $$->addChild($4);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_INTERNAL_BLOCK));
    }
    | DOT_CLOUD ID '(' properties ')' '{' dot_cloud_blocks '}' {
        $$ = new AST::Node(GRAMMERCONSTANTS::DOT_CLOUD);
        delete $1;

        AST::Node* id = new AST::Node(GRAMMERCONSTANTS::ID);
        id->addChild(new AST::Node(*$2));
        $$->addChild(id);
        delete $2;

        $$->addChild(new AST::Node("("));
        $$->addChild($4);
        $$->addChild(new AST::Node(")"));

        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_INTERNAL_BLOCK));
        $$->addChild($7);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_INTERNAL_BLOCK));
    }
;

dot_cloud_blocks:
    /* empty */ {
        $$ = new AST::Node(GRAMMERCONSTANTS::DOT_CLOUD_INTERNAL_BLOCKS);
    }
    | dot_cloud_blocks dot_cloud_block {
        $1->addChild($2);
        $$ = $1;
    }
;

dot_cloud_block:
    '{' properties '}' {
        $$ = new AST::Node(GRAMMERCONSTANTS::DOT_BLOCK);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_DOT_BLOCK));
        $$->addChild($2);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_DOT_BLOCK));
    }
;

object_decl:
    SHAPE ID {

        $$ = new AST::Node(GRAMMERCONSTANTS::OBJECT_DECL);
        AST::Node* shape = new AST::Node(GRAMMERCONSTANTS::SHAPE);
        shape->addChild(new AST::Node(*$1));
        $$->addChild(shape);
        delete $1;

        AST::Node* id = new AST::Node(GRAMMERCONSTANTS::ID);
        id->addChild(new AST::Node(*$2));
        $$->addChild(id);
        delete $2;
    }
    | SHAPE ID '{' properties '}' {

        $$ = new AST::Node(GRAMMERCONSTANTS::OBJECT_DECL);
        AST::Node* shape = new AST::Node(GRAMMERCONSTANTS::SHAPE);
        shape->addChild(new AST::Node(*$1));
        $$->addChild(shape);
        delete $1;

        AST::Node* id = new AST::Node(GRAMMERCONSTANTS::ID);
        id->addChild(new AST::Node(*$2));
        $$->addChild(id);
        delete $2;

        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_INTERNAL_BLOCK));
        $$->addChild($4);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_INTERNAL_BLOCK));
    }
;

relation:
    ID ARROW ID {
        $$ = new AST::Node(GRAMMERCONSTANTS::RELATION);
        AST::Node* fromId = new AST::Node(GRAMMERCONSTANTS::ID);
        fromId->addChild(new AST::Node(*$1));
        $$->addChild(fromId);
        delete $1;

        AST::Node* arrow = new AST::Node(GRAMMERCONSTANTS::ARROW);
        arrow->addChild(new AST::Node(*$2));
        $$->addChild(arrow);
        delete $2;

        AST::Node* toId = new AST::Node(GRAMMERCONSTANTS::ID);
        toId->addChild(new AST::Node(*$3));
        $$->addChild(toId);
        delete $3;
    }
    | ID ARROW ID '{' properties '}' {
        $$ = new AST::Node(GRAMMERCONSTANTS::RELATION);
        AST::Node* fromId = new AST::Node(GRAMMERCONSTANTS::ID);
        fromId->addChild(new AST::Node(*$1));
        $$->addChild(fromId);
        delete $1;

        AST::Node* arrow = new AST::Node(GRAMMERCONSTANTS::ARROW);
        arrow->addChild(new AST::Node(*$2));
        $$->addChild(arrow);
        delete $2;

        AST::Node* toId = new AST::Node(GRAMMERCONSTANTS::ID);
        toId->addChild(new AST::Node(*$3));
        $$->addChild(toId);
        delete $3;

        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_INTERNAL_BLOCK));
        $$->addChild($5);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_INTERNAL_BLOCK));
    }
;

note:
    NOTE ID {
        $$ = new AST::Node(GRAMMERCONSTANTS::NOTE);
        delete $1;

        AST::Node* id = new AST::Node(GRAMMERCONSTANTS::ID);
        id->addChild(new AST::Node(*$2));
        $$->addChild(id);
        delete $2;
    }
    | NOTE ID '{' properties '}' {
        $$ = new AST::Node(GRAMMERCONSTANTS::NOTE);
        delete $1;

        AST::Node* id = new AST::Node(GRAMMERCONSTANTS::ID);
        id->addChild(new AST::Node(*$2));
        $$->addChild(id);
        delete $2;

        $$->addChild(new AST::Node(GRAMMERCONSTANTS::START_INTERNAL_BLOCK));
        $$->addChild($4);
        $$->addChild(new AST::Node(GRAMMERCONSTANTS::END_INTERNAL_BLOCK));
    }
;

properties:
    /* empty */ {
        $$ = new AST::Node(GRAMMERCONSTANTS::PROPERTIES);
    }
    | properties property {
        $1->addChild($2);
        $$ = $1;
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


