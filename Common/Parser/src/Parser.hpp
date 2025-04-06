#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>

#include "AST.hpp"

class Parser
{
public:
    explicit Parser(std::string const& filepath): filepath(filepath) {}
    std::unique_ptr<AST::ASTTree> parse();

private:
    const std::string filepath;
};

#endif // PARSER_H
