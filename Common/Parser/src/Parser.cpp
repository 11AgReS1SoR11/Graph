#include "Parser.h"

std::unique_ptr<AST::ASTTree> Parser::parse()
{
    FILE* input_file = fopen(filepath.c_str(), "r");

    if (!input_file) {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return nullptr;
    }

    yyin = input_file;

    if (yyparse() == 0)
    {
        fclose(input_file);
        return std::move(astTree);
    }

    fclose(input_file);
    astTree.reset();
    return nullptr;
}


