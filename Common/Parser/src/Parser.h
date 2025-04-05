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
extern FILE* yyin;

class Parser
{
public:
    explicit Parser(const std::string filepath): filepath(filepath) {}
    AST::ASTTree* parse();

private:
    const std::string filepath;
};

#endif // PARSER_H
