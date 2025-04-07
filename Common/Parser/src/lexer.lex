%{
#include <iostream>
#include <string>
#include "_parser_.h"

bool is_prop = false;

%}

%option yylineno
%option noyywrap

%x TEXT_MODE

%%

"@startgraph"   {
#ifdef DEBUG
    std::cout << "TOKEN: START_GRAPH" << std::endl;
#endif
    return START_GRAPH;
}

"@endgraph"     {
#ifdef DEBUG
    std::cout << "TOKEN: END_GRAPH" << std::endl;
#endif
    return END_GRAPH;
}

"circle"|"rectangle"|"diamond" {
#ifdef DEBUG
    std::cout << "TOKEN: SHAPE (" << yytext << ")" << std::endl;
#endif
    yylval.str = new std::string(yytext);
    return SHAPE;
}

"->"|"-->"|"<->"|"<-->"|"--"|"-"|"<--"|"<"|">" {
#ifdef DEBUG
    std::cout << "TOKEN: ARROW (" << yytext << ")" << std::endl;
#endif
    yylval.str = new std::string(yytext);
    return ARROW;
}

"note" {
#ifdef DEBUG
    std::cout << "TOKEN: NOTE (" << yytext << ")" << std::endl;
#endif
    yylval.str = new std::string(yytext);
    return NOTE;
}

"graph" {
#ifdef DEBUG
    std::cout << "TOKEN: GRAPH (" << yytext << ")" << std::endl;
#endif
    yylval.str = new std::string(yytext);
    return GRAPH;
}

"color"|"text"|"border"|"x"|"y"|"size_text"|"size_A"|"size_B"|"angle"|"radius"|"grid" {
    is_prop = true;
#ifdef DEBUG
    std::cout << "TOKEN: PROPERTY_KEY (" << yytext << ")" << std::endl;
#endif
    yylval.str = new std::string(yytext);
    return PROPERTY_KEY;
}

[0-9]+ {

    if(is_prop) is_prop = false;
#ifdef DEBUG
    std::cout << "TOKEN: NUMBER (" << yytext << ")" << std::endl;
#endif
    yylval.str = new std::string(yytext);
    return NUMBER;
}

[a-zA-Z][a-zA-Z0-9_]* {

    if(is_prop)
    {
        is_prop = false;
#ifdef DEBUG
        std::cout << "TOKEN: TEXT (" << yytext << ")" << std::endl;
#endif
        yylval.str = new std::string(yytext);
        return TEXT;
    }
    else
    {
#ifdef DEBUG
        std::cout << "TOKEN: ID (" << yytext << ")" << std::endl;
#endif
        yylval.str = new std::string(yytext);
        return ID;
    }
}


\"              { BEGIN(TEXT_MODE); }
<TEXT_MODE>[a-zA-Z0-9,.!? -]+ {

    if(is_prop) is_prop = false;
#ifdef DEBUG
    std::cout << "TOKEN: TEXT (" << yytext << ")" << std::endl;
#endif
    yylval.str = new std::string(yytext);
    return TEXT;
}
<TEXT_MODE>\"   { BEGIN(INITIAL); }


[ \t\r\n]+      { }

[{};=()] {
#ifdef DEBUG
    std::cout << "TOKEN: SYMBOL (" << yytext << ")" << std::endl;
#endif
    return *yytext;
}

. {
#ifdef DEBUG
    std::cout << "TOKEN: UNKNOWN (" << yytext << ")" << std::endl;
#endif
    return *yytext;
}

%%
