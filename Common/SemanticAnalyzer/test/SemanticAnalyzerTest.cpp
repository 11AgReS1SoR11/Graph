#include <QtTest>

#include "SemanticAnalyzer.h"
#include "AstStatementParser.h"

class SemanticAnalyzerTest : public QObject
{
    Q_OBJECT

public:
    SemanticAnalyzerTest() = default;
    ~SemanticAnalyzerTest() = default;

private slots:
    void test_cases();

private:
    AST::ASTTree createSampleAST();
};


AST::ASTTree SemanticAnalyzerTest::createSampleAST()
{
    AST::ASTTree ast(new AST::Node("Program"));

    auto programIt = ast.begin();

    ast.insert(new AST::Node("@startgraph"), programIt);

    {
        AST::Node* statement1 = new AST::Node("statement");
        {
            AST::Node* objectDecl1 = new AST::Node("object_decl");
            {
                objectDecl1->addChild(new AST::Node("SHAPE"));
                {
                    objectDecl1->childNodes.back()->addChild(new AST::Node("rectangle"));
                }
            }

            {
                objectDecl1->addChild(new AST::Node("ID"));
                {
                    objectDecl1->childNodes.back()->addChild(new AST::Node("warshall_algorithm"));
                }
            }

            {
                objectDecl1->addChild(new AST::Node("{"));
            }

            {
                AST::Node* property1 = new AST::Node("property");
                {
                    property1->addChild(new AST::Node("PROPERTY_KEY"));
                    {
                        property1->childNodes.back()->addChild(new AST::Node("font"));
                    }

                    property1->addChild(new AST::Node("="));

                    property1->addChild(new AST::Node("TEXT"));
                    {
                        property1->childNodes.back()->addChild(new AST::Node("calibri"));
                    }
                }
                objectDecl1->addChild(property1);
            }

            {
                objectDecl1->addChild(new AST::Node(";"));
            }

            {
                objectDecl1->addChild(new AST::Node("}"));
            }

            statement1->addChild(objectDecl1);
        }
    }

    ast.insert(new AST::Node("@endgraph"), programIt);

    return ast;
}


void SemanticAnalyzerTest::test_cases()
{
    {
        AST::ASTTree tree = createSampleAST();

        SEMANTICANALYZER::AstStatementParser parser(tree);
        auto programTree = parser.parse();

        SEMANTICANALYZER::SemanticAnalyzer& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
        analyzer.reset();

        QVERIFY(programTree.size() == 1);
        QVERIFY(programTree[0].first == OBJECT_DECL);

        try
        {
            analyzer.semanticAnalysis(programTree, 1);
            QVERIFY(true);
        }
        catch (const SEMANTICANALYZER::SemanticError& error)
        {
            QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
        }

        QVERIFY(analyzer.getDeclaredObjects().count("obj1") == 1);
    }
}


QTEST_APPLESS_MAIN(SemanticAnalyzerTest)

#include "SemanticAnalyzerTest.moc"
