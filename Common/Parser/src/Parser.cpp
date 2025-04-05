#include "Parser.h"

AST::ASTTree *Parser::yyparse()
{
    ast_tree = nullptr;
    int result = ::yyparse();

    if (result == 0) {
        return ast_tree;
    }

    if (ast_tree) {
        delete ast_tree;
    }

    return nullptr;
}

int Parser::parse()
{
    AST::ASTTree* tree = yyparse();

    if (tree)
    {
        printf("Parsing successful!\n");
        delete tree;
    }

    return 0;
}


