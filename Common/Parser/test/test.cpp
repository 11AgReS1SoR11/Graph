#include <catch2/catch_test_macros.hpp>

#include "Parser.h"

#include <iostream>

#define REQUIRE_MESSAGE(condition, message) {if (!(condition)) {FAIL(message);}}

TEST_CASE("test parser ", "[Parser]")
{
    Parser parser;
    AST::ASTTree* astTree = parser.parse();

    AST::ASTTree::DSFIterator astIter;

    for(astIter = (*astTree).begin(); astIter != (*astTree).end(); ++astIter)
    {
        std::cout << astIter.get()->value << std::endl;
    }
}

