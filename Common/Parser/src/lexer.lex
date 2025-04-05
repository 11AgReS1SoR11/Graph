%{
#include <iostream>
#include <string>
#include "parser.h"
%}

%option yylineno
%option noyywrap

%%

"@startgraph"   { std::cout << "TOKEN: START_GRAPH" << std::endl; return START_GRAPH; }
"@endgraph"     { std::cout << "TOKEN: END_GRAPH" << std::endl; return END_GRAPH; }

"circle"        { std::cout << "TOKEN: SHAPE (circle)" << std::endl; yylval.str = new std::string(yytext); return SHAPE; }
"rectangle"     { std::cout << "TOKEN: SHAPE (rectangle)" << std::endl; yylval.str = new std::string(yytext); return SHAPE; }
"diamond"       { std::cout << "TOKEN: SHAPE (diamond)" << std::endl; yylval.str = new std::string(yytext); return SHAPE; }

"color"         { std::cout << "TOKEN: PROPERTY_KEY (color)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"text"          { std::cout << "TOKEN: PROPERTY_KEY (text)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"border"        { std::cout << "TOKEN: PROPERTY_KEY (border)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"x"             { std::cout << "TOKEN: PROPERTY_KEY (x)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"y"             { std::cout << "TOKEN: PROPERTY_KEY (y)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"size_text"     { std::cout << "TOKEN: PROPERTY_KEY (size_text)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"radius"        { std::cout << "TOKEN: PROPERTY_KEY (radius)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"size_A"        { std::cout << "TOKEN: PROPERTY_KEY (size_A)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"size_B"        { std::cout << "TOKEN: PROPERTY_KEY (size_B)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"angle"         { std::cout << "TOKEN: PROPERTY_KEY (angle)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }
"grid"          { std::cout << "TOKEN: PROPERTY_KEY (grid)" << std::endl; yylval.str = new std::string(yytext); return PROPERTY_KEY; }

[a-zA-Z][a-zA-Z0-9_]* {
    if (strcmp(yytext, "circle") == 0 || strcmp(yytext, "rectangle") == 0 || strcmp(yytext, "diamond") == 0) {
        REJECT;
    }
    else {
        std::cout << "TOKEN: ID (" << yytext << ")" << std::endl;
        yylval.str = new std::string(yytext);
        return ID;
    }
}

[0-9]+ {
    std::cout << "TOKEN: NUMBER (" << yytext << ")" << std::endl;
    yylval.str = new std::string(yytext);
    return NUMBER;
}

[ \t\r\n]+ ;

[{};=] {
    std::cout << "TOKEN: SYMBOL (" << yytext << ")" << std::endl;
    return *yytext;
}

. {
    std::cout << "TOKEN: UNKNOWN (" << yytext << ")" << std::endl;
    return *yytext;
}

%%
