#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "AST.hpp"

using namespace AST;

TEST_CASE("initialization", "[AST]")
{
    Node* root = new Node("PROGRAM");
    ASTTree tree(root);

    auto it = tree.begin();
    REQUIRE(it != tree.end());
    REQUIRE(it->getValue() == "PROGRAM");
}

TEST_CASE("insert to begin tree", "[AST]")
{
    ASTTree tree;

    { // insert first node to empty tree
        Node* node = new Node("PROGRAM");
        // auto it = tree.begin();
        tree.insert(node, tree.begin());

        auto it = tree.begin();
        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "PROGRAM");

        ++it;

        REQUIRE(it == tree.end());
    }

    { // insert second node to tree
        Node* node = new Node("@startgraph");
        tree.insert(node, tree.begin());

        auto it = tree.begin();
        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "PROGRAM");

        ++it;

        REQUIRE(it != tree.end());
        
        REQUIRE(it->getValue() == "@startgraph");

        ++it;

        REQUIRE(it == tree.end());
    }

    { // insert third node to tree
        Node* node = new Node("@endgraph");
        tree.insert(node, tree.begin());

        auto it = tree.begin();
        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "PROGRAM");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "@startgraph");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "@endgraph");

        ++it;

        REQUIRE(it == tree.end());
    }
}

TEST_CASE("insert to any node of tree", "[AST]")
{
    Node* root = new Node("PROGRAM");
    ASTTree tree(root);

    // insert after PROGRAM
    Node* nodeStatement = new Node("statement");
    auto itStatement = tree.insert(nodeStatement, tree.begin());
    REQUIRE(itStatement != tree.end());
    REQUIRE(itStatement->getValue() == "statement");

    // insert after STATEMENT
    Node* nodeRelation = new Node("RELATION");
    auto itRelation = tree.insert(nodeRelation, itStatement);
    REQUIRE(itRelation != tree.end());
    REQUIRE(itRelation->getValue() == "RELATION");

    // insert after RELATION
    Node* nodePointer = new Node("<--");
    auto itPointer = tree.insert(nodePointer, itRelation);
    REQUIRE(itPointer != tree.end());
    REQUIRE(itPointer->getValue() == "<--");

    { // check tree sturcture
        auto it = tree.begin();
        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "PROGRAM");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "statement");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "RELATION");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "<--");

        ++it;

        REQUIRE(it == tree.end());
    }

    // insert after PROGRAM
    Node* nodeStatement2 = new Node("statement");
    auto itStatement2 = tree.insert(nodeStatement2, tree.begin());
    REQUIRE(itStatement2 != tree.end());
    REQUIRE(itStatement2->getValue() == "statement");

    // insert after RELATION
    Node* nodeID = new Node("ID");
    auto itID = tree.insert(nodeID, itRelation);
    REQUIRE(itID != tree.end());
    REQUIRE(itID->getValue() == "ID");

    { // check tree sturcture
        auto it = tree.begin();
        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "PROGRAM");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "statement");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "RELATION");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "<--");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "ID");

        ++it;

        REQUIRE(it != tree.end());
        REQUIRE(it->getValue() == "statement");

        ++it;

        REQUIRE(it == tree.end());
    }
}

TEST_CASE("range for", "[AST]")
{
    Node* root = new Node("PROGRAM");
    ASTTree tree(root);

    // insert after PROGRAM
    Node* nodeStatement = new Node("statement");
    auto itStatement = tree.insert(nodeStatement, tree.begin());
    REQUIRE(itStatement != tree.end());
    REQUIRE(itStatement->getValue() == "statement");

    // insert after STATEMENT
    Node* nodeRelation = new Node("RELATION");
    auto itRelation = tree.insert(nodeRelation, itStatement);
    REQUIRE(itRelation != tree.end());
    REQUIRE(itRelation->getValue() == "RELATION");

    // insert after RELATION
    Node* nodePointer = new Node("<--");
    auto itPointer = tree.insert(nodePointer, itRelation);
    REQUIRE(itPointer != tree.end());
    REQUIRE(itPointer->getValue() == "<--");

    int idx = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it, ++idx)
    {
        if (idx == 0) { REQUIRE(it->getValue() == "PROGRAM"); }
        if (idx == 1) { REQUIRE(it->getValue() == "statement"); }
        if (idx == 2) { REQUIRE(it->getValue() == "RELATION"); }
        if (idx == 3) { REQUIRE(it->getValue() == "<--"); }
    }
}

TEST_CASE("DFSIterators compare", "[AST]")
{
    SECTION("Compare begin and end iterators")
    {
        Node* root = new Node("PROGRAM");
        ASTTree tree(root);

        REQUIRE(tree.begin() != tree.end());
        REQUIRE(++tree.begin() == tree.end());
    }

    SECTION("Compare all tree's iterators")
    {
        ASTTree tree;
        REQUIRE(tree.begin() == tree.end());

        Node* root = new Node("PROGRAM");
        auto it = tree.insert(root, tree.begin());

        REQUIRE(tree.begin() != tree.end());
        REQUIRE(tree.begin() == it);

        REQUIRE(++tree.begin() == tree.end());
        REQUIRE(it != tree.end());
        REQUIRE(++it == tree.end());
    }
}

TEST_CASE("Unsuccesful outcome", "[AST][rainy]")
{
    Node* root = new Node("PROGRAM");
    ASTTree tree(root);

    REQUIRE_THROWS_WITH(tree.insert(nullptr, tree.begin()), "Insert nullptr, bug!?");

    auto it = tree.end();
    REQUIRE_THROWS_WITH(*it, "Dereference empty iter, bug!?");
    REQUIRE_THROWS_WITH(it->getValue(), "Dereference empty iter, bug!?");
}
