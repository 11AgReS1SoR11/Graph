#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>

#include "AST.hpp"

extern std::unique_ptr<AST::ASTTree> astTree;
extern int yyparse(void);
extern FILE* yyin;

class Parser
{
public:
    explicit Parser(const std::string filepath): filepath(filepath) {}
    std::unique_ptr<AST::ASTTree> parse();

private:
    const std::string filepath;
};

#endif // PARSER_H
