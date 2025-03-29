#ifndef ASTSTATEMENTPARSER_H
#define ASTSTATEMENTPARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

#include "AST.hpp"
#include "Logger.hpp"
#include "SemanticAnalyzer.h"

namespace SEMANTICANALYZER {

class AstStatementParser
{
public:
    explicit AstStatementParser(AST::ASTTree& astTree): astTree(astTree) {}

    std::vector<std::pair<std::string, std::any>>& parse() noexcept;

private:
    void serializeObjectDec(AST::ASTTree::DSFIterator& objectDecIter, ObjectDecl& objectDecl) noexcept;
    void serializeRelation(AST::ASTTree::DSFIterator& relationIter, Relation& relation) noexcept;
    void serializeNote(AST::ASTTree::DSFIterator& noteIter, Note& note) noexcept;
    void serializeGraph(AST::ASTTree::DSFIterator& graphIter, Graph& graph) noexcept;
    void serializeDotCloud(AST::ASTTree::DSFIterator& dotCloudIter, DotCloud& dotCloud) noexcept;
    void serializeProperty(AST::ASTTree::DSFIterator& propertyIter, Property& property) noexcept;

private:
    AST::ASTTree& astTree;
    std::vector<std::pair<std::string, std::any>> programTree;
};

}

#endif // ASTSTATEMENTPARSER_H
