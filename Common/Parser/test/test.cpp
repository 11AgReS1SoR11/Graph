#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "Parser.hpp"

TEST_CASE("test1 object_decl ", "[Parser]")
{
    Parser parser("tests/test1");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();

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
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();

    AST::ASTTree::DSFIterator astIter;

#ifdef DEBUG
    for(astIter = (*astTree).begin(); astIter != (*astTree).end(); ++astIter)
    {
        std::cout << astIter.get()->value << std::endl;
    }
#endif

}


TEST_CASE("test3 object_decl/relation ", "[Parser]")
{
    Parser parser("tests/test3");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();

    AST::ASTTree::DSFIterator astIter;

#ifdef DEBUG
    for(astIter = (*astTree).begin(); astIter != (*astTree).end(); ++astIter)
    {
        std::cout << astIter.get()->value << std::endl;
    }
#endif

}


TEST_CASE("test4 object_decl/relation/note ", "[Parser]")
{
    Parser parser("tests/test4");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();

    AST::ASTTree::DSFIterator astIter;

#ifdef DEBUG
    for(astIter = (*astTree).begin(); astIter != (*astTree).end(); ++astIter)
    {
        std::cout << astIter.get()->value << std::endl;
    }
#endif

}


TEST_CASE("test5 graph ", "[Parser]")
{
    Parser parser("tests/test5");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();

    AST::ASTTree::DSFIterator astIter;

#ifdef DEBUG
    for(astIter = (*astTree).begin(); astIter != (*astTree).end(); ++astIter)
    {
        std::cout << astIter.get()->value << std::endl;
    }
#endif

}
