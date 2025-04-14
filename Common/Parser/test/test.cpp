#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "Parser.hpp"
#include "Logger.hpp"

TEST_CASE("test1 object_decl ", "[Parser]")
{
    LOG_INFO(PARSER_LOG, "TEST CASE1:")
    Parser parser("tests/test1");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();
    REQUIRE(astTree);
    LOG_INFO(PARSER_LOG, "TEST COMPLETE SUCCESFUL!\n\n")
}


TEST_CASE("test2 object_decl ", "[Parser]")
{
    LOG_INFO(PARSER_LOG, "TEST CASE2:")
    Parser parser("tests/test2");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();
    REQUIRE(astTree);
    LOG_INFO(PARSER_LOG, "TEST COMPLETE SUCCESFUL!\n\n")
}


TEST_CASE("test3 object_decl/relation ", "[Parser]")
{
    LOG_INFO(PARSER_LOG, "TEST CASE3:")
    Parser parser("tests/test3");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();
    REQUIRE(astTree);
    LOG_INFO(PARSER_LOG, "TEST COMPLETE SUCCESFUL!\n\n")
}


TEST_CASE("test4 object_decl/relation/note ", "[Parser]")
{
    LOG_INFO(PARSER_LOG, "TEST CASE4:")
    Parser parser("tests/test4");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();
    REQUIRE(astTree);
    LOG_INFO(PARSER_LOG, "TEST COMPLETE SUCCESFUL!\n\n")
}


TEST_CASE("test5 graph ", "[Parser]")
{
    LOG_INFO(PARSER_LOG, "TEST CASE5:")
    Parser parser("tests/test5");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();
    REQUIRE(astTree);
    LOG_INFO(PARSER_LOG, "TEST COMPLETE SUCCESFUL!\n\n")
}


TEST_CASE("test6 dot_cloud ", "[Parser]")
{
    LOG_INFO(PARSER_LOG, "TEST CASE6:")
    Parser parser("tests/test6");
    std::unique_ptr<AST::ASTTree> astTree = parser.parse();
    REQUIRE(astTree);
    LOG_INFO(PARSER_LOG, "TEST COMPLETE SUCCESFUL!\n\n")
}
