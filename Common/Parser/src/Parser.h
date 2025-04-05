#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

#include "Logger.hpp"
#include "AST.hpp"

extern "C" AST::ASTTree* ast_tree;

// Переопределяем yyparse для возврата AST::ASTTree*
extern "C" int yyparse(void);



class Parser
{
public:
    Parser() = default;
    AST::ASTTree* yyparse();
    int parse();
};

#endif // PARSER_H
