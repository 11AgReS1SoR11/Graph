#include "Parser.h"

AST::ASTTree* Parser::parse()
{
    astTree = nullptr;

    if (yyparse() == 0) {
        return astTree;
    }

    return nullptr;
}


