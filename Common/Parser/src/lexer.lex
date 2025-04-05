%{
#include <iostream>
#include <string>

#include "parser.h"
#include "SemanticAnalyzer.hpp"
%}

%option yylineno
%option noyywrap

%%

"@startgraph"   { return START_GRAPH; }
"@endgraph"     { return END_GRAPH; }
"circle"        { yylval.str = new std::string("circle"); return SHAPE; }
"rectangle"     { yylval.str = new std::string("rectangle"); return SHAPE; }
"diamond"       { yylval.str = new std::string("diamond"); return SHAPE; }

"color"         { yylval.str = new std::string("color"); return PROPERTY_KEY; }
"text"          { yylval.str = new std::string("text"); return PROPERTY_KEY; }
"border"        { yylval.str = new std::string("border"); return PROPERTY_KEY; }
"x"             { yylval.str = new std::string("x"); return PROPERTY_KEY; }
"y"             { yylval.str = new std::string("y"); return PROPERTY_KEY; }
"size_text"     { yylval.str = new std::string("size_text"); return PROPERTY_KEY; }
"radius"        { yylval.str = new std::string("radius"); return PROPERTY_KEY; }
"size_A"        { yylval.str = new std::string("size_A"); return PROPERTY_KEY; }
"size_B"        { yylval.str = new std::string("size_B"); return PROPERTY_KEY; }
"angle"         { yylval.str = new std::string("angle"); return PROPERTY_KEY; }
"grid"          { yylval.str = new std::string("grid"); return PROPERTY_KEY; }

"red"|"blue"|"green"|"black"|"white"|"yellow"|"purple" {
    yylval.str = new std::string(yytext); return TEXT;
}

[a-zA-Z][a-zA-Z0-9_]* { yylval.str = new std::string(yytext); return ID; }
[0-9]+                { yylval.str = new std::string(yytext); return NUMBER; }
[ \t\r\n]             ;
[{};=]                { return *yytext; }
.                     { return *yytext; }

%%
