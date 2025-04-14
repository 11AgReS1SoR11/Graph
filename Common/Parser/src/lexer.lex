%{
#include <iostream>
#include <string>
#include <sstream>
#include "_parser_.h"

#include "Logger.hpp"

bool is_prop = false;
bool is_text = false;

%}

%option yylineno
%option noyywrap

%x TEXT_MODE

%%

"@startgraph"   {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: START_GRAPH";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    return START_GRAPH;
}

"@endgraph"     {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: END_GRAPH";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    return END_GRAPH;
}

"circle"|"rectangle"|"diamond" {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: SHAPE (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return SHAPE;
}

"->"|"-->"|"<->"|"<-->"|"--"|"-"|"<--"|"<"|">" {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: ARROW (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return ARROW;
}

"note" {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: NOTE (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return NOTE;
}

"graph" {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: GRAPH (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return GRAPH;
}

"dot_cloud" {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: DOT_CLOUD (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return DOT_CLOUD;
}

"color"|"text"|"border"|"x"|"y"|"size_text"|"size_A"|"size_B"|"angle"|"radius"|"grid" {
    is_prop = true;
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: PROPERTY_KEY (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return PROPERTY_KEY;
}

[0-9]+ {
    if(is_prop) is_prop = false;
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: NUMBER (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return NUMBER;
}

[0-9]+\.[0-9]+ {
    if(is_prop) is_prop = false;
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: NUMBER (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return NUMBER;
}

[a-zA-Z][a-zA-Z0-9_]* {
    if(is_prop)
    {
        is_prop = false;
#ifdef DEBUG
        std::ostringstream debugMsg;
        debugMsg << "TOKEN: TEXT (" << yytext << ")";
        LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
        yylval.str = new std::string(yytext);
        return TEXT;
    }
    else
    {
#ifdef DEBUG
        std::ostringstream debugMsg;
        debugMsg << "TOKEN: ID (" << yytext << ")";
        LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
        yylval.str = new std::string(yytext);
        return ID;
    }
}

\"  { BEGIN(TEXT_MODE); }

<TEXT_MODE>[a-zA-Z0-9,.!? -]+ {
    if(is_prop) is_prop = false;
    is_text = true;
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: TEXT (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    yylval.str = new std::string(yytext);
    return TEXT;
}

<TEXT_MODE>\"   {
    if(is_prop) is_prop = false;
    if(!is_text) {
#ifdef DEBUG
        std::ostringstream debugMsg;
        debugMsg << "TOKEN: TEXT (empty)";
        LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
        yylval.str = new std::string("");
        BEGIN(INITIAL);
        return TEXT;
    }
    else {
        is_text = false;
        BEGIN(INITIAL);
    }
}

"//"[^\n]* {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "COMMENT: (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
}

[ \t\r\n]+      { }

[{};=()] {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: SYMBOL (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    return *yytext;
}

. {
#ifdef DEBUG
    std::ostringstream debugMsg;
    debugMsg << "TOKEN: UNKNOWN (" << yytext << ")";
    LOG_INFO(PARSER_LOG, debugMsg.str());
#endif
    return *yytext;
}

%%
