#include <catch2/catch_test_macros.hpp>

#include "Parser.h"

#include <iostream>

#define REQUIRE_MESSAGE(condition, message) {if (!(condition)) {FAIL(message);}}

TEST_CASE("test1 object_decl ", "[Parser]")
{
    Parser parser("tests/test1");
    AST::ASTTree* astTree = parser.parse();

    AST::ASTTree::DSFIterator astIter;

#ifdef DEBUG
    for(astIter = (*astTree).begin(); astIter != (*astTree).end(); ++astIter)
    {
        std::cout << astIter.get()->value << std::endl;
    }
#endif
}


TEST_CASE("test2 object_decl ", "[Parser]")
{
    Parser parser("tests/test2");
    AST::ASTTree* astTree = parser.parse();

    AST::ASTTree::DSFIterator astIter;

#ifdef DEBUG
    for(astIter = (*astTree).begin(); astIter != (*astTree).end(); ++astIter)
    {
        std::cout << astIter.get()->value << std::endl;
    }
#endif
}


TEST_CASE("test3 relation ", "[Parser]")
{
    Parser parser("tests/test3");
    AST::ASTTree* astTree = parser.parse();

    AST::ASTTree::DSFIterator astIter;

#ifdef DEBUG
    for(astIter = (*astTree).begin(); astIter != (*astTree).end(); ++astIter)
    {
        std::cout << astIter.get()->value << std::endl;
    }
#endif
}
