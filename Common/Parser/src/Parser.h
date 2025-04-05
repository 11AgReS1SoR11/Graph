#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

#include "AST.hpp"

extern AST::ASTTree* astTree;
extern int yyparse(void);


class Parser
{
public:
    Parser() = default;
    AST::ASTTree* parse();
};

#endif // PARSER_H
