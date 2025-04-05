#include "Parser.h"

AST::ASTTree* Parser::parse()
{
    if(astTree != nullptr)
        delete astTree;

    FILE* input_file = fopen(filepath.c_str(), "r");

    if(!input_file)
    {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return nullptr;
    }

    yyin = input_file;

    if (yyparse() == 0)
    {
        fclose(input_file);
        return astTree;
    }

    fclose(input_file);
    return nullptr;
}


