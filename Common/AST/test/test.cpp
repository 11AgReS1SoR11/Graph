#include <QtTest/QtTest>
#include <stdexcept>
#include "AST.hpp"

using namespace AST;

class TestClass : public QObject
{
    Q_OBJECT

private slots:
    void test_initializeTree();
    void test_insertToBeginTree();
    void test_insertToAnyNodeTree();
    void test_rangeForTree();
    void test_TreeIterCompare();
    void test_failureCaseTree();
};

void TestClass::test_initializeTree()
{
    Node* root = new Node("PROGRAM");
    ASTTree tree(root);

    auto it = tree.begin();
    QVERIFY(it != tree.end());
    QVERIFY(it->getValue() == "PROGRAM");
}

void TestClass::test_insertToBeginTree()
{
    ASTTree tree;

    { // insert first node to empty tree
        Node* node = new Node("PROGRAM");
        // auto it = tree.begin();
        tree.insert(node, tree.begin());

        auto it = tree.begin();
        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "PROGRAM");

        ++it;

        QVERIFY(it == tree.end());
    }

    { // insert second node to tree
        Node* node = new Node("@startgraph");
        tree.insert(node, tree.begin());

        auto it = tree.begin();
        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "PROGRAM");

        ++it;

        QVERIFY(it != tree.end());
        
        QVERIFY(it->getValue() == "@startgraph");

        ++it;

        QVERIFY(it == tree.end());
    }

    { // insert third node to tree
        Node* node = new Node("@endgraph");
        tree.insert(node, tree.begin());

        auto it = tree.begin();
        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "PROGRAM");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "@startgraph");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "@endgraph");

        ++it;

        QVERIFY(it == tree.end());
    }
}

void TestClass::test_insertToAnyNodeTree()
{
    Node* root = new Node("PROGRAM");
    ASTTree tree(root);

    // insert after PROGRAM
    Node* nodeStatement = new Node("STATEMENT");
    auto itStatement = tree.insert(nodeStatement, tree.begin());
    QVERIFY(itStatement != tree.end());
    QVERIFY(itStatement->getValue() == "STATEMENT");

    // insert after STATEMENT
    Node* nodeRelation = new Node("RELATION");
    auto itRelation = tree.insert(nodeRelation, itStatement);
    QVERIFY(itRelation != tree.end());
    QVERIFY(itRelation->getValue() == "RELATION");

    // insert after RELATION
    Node* nodePointer = new Node("<--");
    auto itPointer = tree.insert(nodePointer, itRelation);
    QVERIFY(itPointer != tree.end());
    QVERIFY(itPointer->getValue() == "<--");

    { // check tree sturcture
        auto it = tree.begin();
        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "PROGRAM");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "STATEMENT");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "RELATION");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "<--");

        ++it;

        QVERIFY(it == tree.end());
    }

    // insert after PROGRAM
    Node* nodeStatement2 = new Node("STATEMENT");
    auto itStatement2 = tree.insert(nodeStatement2, tree.begin());
    QVERIFY(itStatement2 != tree.end());
    QVERIFY(itStatement2->getValue() == "STATEMENT");

    // insert after RELATION
    Node* nodeID = new Node("ID");
    auto itID = tree.insert(nodeID, itRelation);
    QVERIFY(itID != tree.end());
    QVERIFY(itID->getValue() == "ID");

    { // check tree sturcture
        auto it = tree.begin();
        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "PROGRAM");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "STATEMENT");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "RELATION");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "<--");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "ID");

        ++it;

        QVERIFY(it != tree.end());
        QVERIFY(it->getValue() == "STATEMENT");

        ++it;

        QVERIFY(it == tree.end());
    }
}

void TestClass::test_rangeForTree()
{
    Node* root = new Node("PROGRAM");
    ASTTree tree(root);

    // insert after PROGRAM
    Node* nodeStatement = new Node("STATEMENT");
    auto itStatement = tree.insert(nodeStatement, tree.begin());
    QVERIFY(itStatement != tree.end());
    QVERIFY(itStatement->getValue() == "STATEMENT");

    // insert after STATEMENT
    Node* nodeRelation = new Node("RELATION");
    auto itRelation = tree.insert(nodeRelation, itStatement);
    QVERIFY(itRelation != tree.end());
    QVERIFY(itRelation->getValue() == "RELATION");

    // insert after RELATION
    Node* nodePointer = new Node("<--");
    auto itPointer = tree.insert(nodePointer, itRelation);
    QVERIFY(itPointer != tree.end());
    QVERIFY(itPointer->getValue() == "<--");

    int idx = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it, ++idx)
    {
        if (idx == 0) { QVERIFY(it->getValue() == "PROGRAM"); }
        if (idx == 1) { QVERIFY(it->getValue() == "STATEMENT"); }
        if (idx == 2) { QVERIFY(it->getValue() == "RELATION"); }
        if (idx == 3) { QVERIFY(it->getValue() == "<--"); }
    }
}

void TestClass::test_TreeIterCompare()
{
    {
        Node* root = new Node("PROGRAM");
        ASTTree tree(root);

        QVERIFY(tree.begin() != tree.end());
        QVERIFY(++tree.begin() == tree.end());
    }

    {
        ASTTree tree;
        QVERIFY(tree.begin() == tree.end());

        Node* root = new Node("PROGRAM");
        auto it = tree.insert(root, tree.begin());

        QVERIFY(tree.begin() != tree.end());
        QVERIFY(tree.begin() == it);

        QVERIFY(++tree.begin() == tree.end());
        QVERIFY(it != tree.end());
        QVERIFY(++it == tree.end());
    }
}

void TestClass::test_failureCaseTree()
{
    Node* root = new Node("PROGRAM");
    ASTTree tree(root);

    QVERIFY_EXCEPTION_THROWN(tree.insert(nullptr, tree.begin()), std::runtime_error);

    auto it = tree.end();
    QVERIFY_EXCEPTION_THROWN(*it, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN(it->getValue(), std::runtime_error);
}

QTEST_GUILESS_MAIN(TestClass)
#include "test.moc"
