#ifndef ASTSTATEMENTPARSER_H
#define ASTSTATEMENTPARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

#include "AST.hpp"
#include "SemanticAnalyzer.h"

namespace SEMANTICANALYZER {

class AstStatementParser
{
public:
    AstStatementParser(const AST::ASTTree& astTree): astTree(astTree) {}

    std::vector<std::pair<std::string, std::any>>& parse();

private:
    void serializeObjectDec(AST::ASTTree::DSFIterator& objectDecIter, ObjectDecl& objectDecl);
    void serializeRelation(AST::ASTTree::DSFIterator& relationIter, Relation& relation);
    void serializeNote(AST::ASTTree::DSFIterator& noteIter, Note& note);
    void serializeGraph(AST::ASTTree::DSFIterator& graphIter, Graph& graph);
    void serializeDotCloud(AST::ASTTree::DSFIterator& dotCloudIter, DotCloud& dotCloud);
    void serializeProperty(AST::ASTTree::DSFIterator& propertyIter, Property& property);

private:
    AST::ASTTree astTree;
    std::vector<std::pair<std::string, std::any>> programTree;
};

}

#endif // ASTSTATEMENTPARSER_H
