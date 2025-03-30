#include <QtTest>

#include <iostream>

#include "SemanticAnalyzer.h"
#include "AstStatementParser.h"

class SemanticAnalyzerTest : public QObject
{
    Q_OBJECT

public:
    SemanticAnalyzerTest() = default;
    ~SemanticAnalyzerTest() = default;

private slots:
    void testObjectDecl();
    //    void testRelation();
    //    void testNote();
    //    void testGraph();
    //    void testDotCloud();

private:
    AST::Node* createObjectDeclAST(SEMANTICANALYZER::ObjectDecl& objectDecl);
    AST::Node* createRelationAST(SEMANTICANALYZER::Relation& relation);
    AST::Node* createNoteAST(SEMANTICANALYZER::Note& note);
    AST::Node* createGraphAST(SEMANTICANALYZER::Graph& graph);
    AST::Node* createDotCloudAST(SEMANTICANALYZER::DotCloud& dotCloud);
    AST::Node* createPropertyAST(SEMANTICANALYZER::Property& property);
    AST::Node* createDotAST(SEMANTICANALYZER::Dot& dot);
};


AST::Node* SemanticAnalyzerTest::createObjectDeclAST(SEMANTICANALYZER::ObjectDecl& objectDecl)
{
    AST::Node* statement = new AST::Node(STATEMENT);
    {
        AST::Node* object_decl = new AST::Node(OBJECT_DECL);
        {
            object_decl->addChild(new AST::Node(SHAPE));
            {
                object_decl->childNodes.back()->addChild(new AST::Node(objectDecl.shape));
            }

            object_decl->addChild(new AST::Node(ID));
            {
                object_decl->childNodes.back()->addChild(new AST::Node(objectDecl.id));
            }

            object_decl->addChild(new AST::Node(START_INTERNAL_BLOCK));

            for(auto& prop : objectDecl.properties)
            {
                object_decl->addChild(createPropertyAST(prop));
            }

            object_decl->addChild(new AST::Node(END_INTERNAL_BLOCK));
        }
        statement->addChild(object_decl);
    }

    return statement;
}

AST::Node* SemanticAnalyzerTest::createRelationAST(SEMANTICANALYZER::Relation& rel)
{
    AST::Node* statement = new AST::Node(STATEMENT);
    {
        AST::Node* relation = new AST::Node(RELATION);
        {
            relation->addChild(new AST::Node(ID));
            {
                relation->childNodes.back()->addChild(new AST::Node(rel.id1));
            }

            relation->addChild(new AST::Node(ARROW));
            {
                relation->childNodes.back()->addChild(new AST::Node(rel.arrow));
            }

            relation->addChild(new AST::Node(ID));
            {
                relation->childNodes.back()->addChild(new AST::Node(rel.id2));
            }

            relation->addChild(new AST::Node(START_INTERNAL_BLOCK));

            for(auto& prop : rel.properties)
            {
                relation->addChild(createPropertyAST(prop));
            }

            relation->addChild(new AST::Node(END_INTERNAL_BLOCK));
        }
        statement->addChild(relation);
    }

    return statement;
}

AST::Node* SemanticAnalyzerTest::createNoteAST(SEMANTICANALYZER::Note& strNote)
{
    AST::Node* statement = new AST::Node(STATEMENT);
    {
        AST::Node* note = new AST::Node(NOTE);
        {
            note->addChild(new AST::Node(ID));
            note->childNodes.back()->addChild(new AST::Node(strNote.id));

            note->addChild(new AST::Node(START_INTERNAL_BLOCK));

            for(auto& prop : strNote.properties)
            {
                note->addChild(createPropertyAST(prop));
            }

            note->addChild(new AST::Node(END_INTERNAL_BLOCK));
        }
        statement->addChild(note);
    }

    return statement;
}

AST::Node* SemanticAnalyzerTest::createGraphAST(SEMANTICANALYZER::Graph& strGraph)
{
    AST::Node* statement = new AST::Node(STATEMENT);
    {
        AST::Node* graph = new AST::Node(GRAPH);
        {
            graph->addChild(new AST::Node(ID));
            graph->childNodes.back()->addChild(new AST::Node(strGraph.id));

            graph->addChild(new AST::Node(START_INTERNAL_BLOCK));

            for(auto& objectDecl : strGraph.objects)
            {
                graph->addChild(createObjectDeclAST(objectDecl)->childNodes.front());
            }

            for(auto& relation : strGraph.relations)
            {
                graph->addChild(createRelationAST(relation)->childNodes.front());
            }

            graph->addChild(new AST::Node(END_INTERNAL_BLOCK));
        }
        statement->addChild(graph);
    }

    return statement;
}

AST::Node* SemanticAnalyzerTest::createDotCloudAST(SEMANTICANALYZER::DotCloud& dotCloud)
{
    AST::Node* statement = new AST::Node(STATEMENT);
    {
        AST::Node* dot_cloud = new AST::Node(DOT_CLOUD);
        {
            dot_cloud->addChild(new AST::Node(ID));
            dot_cloud->childNodes.back()->addChild(new AST::Node(dotCloud.id));

            dot_cloud->addChild(new AST::Node(START_INTERNAL_BLOCK));

            for(auto& dot : dotCloud.dots)
            {
                dot_cloud->addChild(createDotAST(dot)->childNodes.front());
            }

            dot_cloud->addChild(new AST::Node(END_INTERNAL_BLOCK));
        }
        statement->addChild(dot_cloud);
    }

    return statement;
}

AST::Node *SemanticAnalyzerTest::createPropertyAST(SEMANTICANALYZER::Property& prop)
{
    AST::Node* property = new AST::Node(PROPERTY);
    {
        property->addChild(new AST::Node(PROPERTY_KEY));
        {
            property->childNodes.back()->addChild(new AST::Node(prop.key));
        }

        property->addChild(new AST::Node("="));

        property->addChild(new AST::Node(TEXT));
        {
            property->childNodes.back()->addChild(new AST::Node(prop.value));
        }

        property->addChild(new AST::Node(";"));
    }

    return property;
}

AST::Node *SemanticAnalyzerTest::createDotAST(SEMANTICANALYZER::Dot &strDot)
{
    AST::Node* dot = new AST::Node(DOT);
    {
        dot->addChild(new AST::Node(START_INTERNAL_BLOCK));

        for(auto& property : strDot.internalProperties)
        {
            dot->addChild(createPropertyAST(property));
        }

        dot->addChild(new AST::Node(END_INTERNAL_BLOCK));
    }

    return dot;
}

void SemanticAnalyzerTest::testObjectDecl()
{
    AST::ASTTree ast(new AST::Node(PROGRAM));
    auto programIt = ast.begin();
    ast.insert(new AST::Node(START_GRAPH), programIt);

    SEMANTICANALYZER::ObjectDecl objectDecl;
    const char* ciEnv = std::getenv("CI");

    if(ciEnv != nullptr && std::string(ciEnv) == "true")
    {
        objectDecl.id = "rect";
        objectDecl.shape = "rectangle";
    }
    else
    {
        std::cout << "Please enter an id of object: " << std::endl;
        std::cin >> objectDecl.id;
        std::cout << "Please enter a shape of object: " << std::endl;
        std::cin >> objectDecl.shape;
        std::cout << "Please enter an number of properties: " << std::endl;
        std::size_t numberProp;
        std::cin >> numberProp;
        for(std::size_t i = 0; i < numberProp; ++i)
        {
            SEMANTICANALYZER::Property property;
            std::cout << "Please enter a key of property number " << i + 1 << " :" << std::endl;
            std::cin >> property.key;
            std::cout << "Please enter a value of property number " << i + 1 << " :" << std::endl;
            std::cin >> property.value;
        }
    }

    ast.insert(createObjectDeclAST(objectDecl), programIt);
    ast.insert(new AST::Node(END_GRAPH), programIt);

    SEMANTICANALYZER::AstStatementParser parser(ast);

    auto programTree = parser.parse();
    SEMANTICANALYZER::SemanticAnalyzer& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
    analyzer.reset();

    QVERIFY(programTree.size() == 1);
    QVERIFY(programTree[0].first == OBJECT_DECL);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);
    }
    catch (const SEMANTICANALYZER::SemanticError& error)
    {
        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}

//void SemanticAnalyzerTest::testRelation()
//{
//    AST::ASTTree ast(new AST::Node(PROGRAM));

//    auto programIt = ast.begin();

//    ast.insert(new AST::Node(START_GRAPH), programIt);
//    ast.insert(createRelationAST(), programIt);
//    ast.insert(new AST::Node(END_GRAPH), programIt);

//    SEMANTICANALYZER::AstStatementParser parser(ast);

//    auto programTree = parser.parse();
//    SEMANTICANALYZER::SemanticAnalyzer& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
//    analyzer.reset();

//    QVERIFY(programTree.size() == 1);
//    QVERIFY(programTree[0].first == RELATION);

//    try
//    {
//        analyzer.semanticAnalysis(programTree, 1);
//    }
//    catch (const SEMANTICANALYZER::SemanticError& error)
//    {
//        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
//    }
//}

//void SemanticAnalyzerTest::testNote()
//{
//    AST::ASTTree ast(new AST::Node(PROGRAM));

//    auto programIt = ast.begin();

//    ast.insert(new AST::Node(START_GRAPH), programIt);
//    ast.insert(createNoteAST(), programIt);
//    ast.insert(new AST::Node(END_GRAPH), programIt);

//    SEMANTICANALYZER::AstStatementParser parser(ast);

//    auto programTree = parser.parse();
//    SEMANTICANALYZER::SemanticAnalyzer& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
//    analyzer.reset();

//    QVERIFY(programTree.size() == 1);
//    QVERIFY(programTree[0].first == NOTE);

//    try
//    {
//        analyzer.semanticAnalysis(programTree, 1);
//    }
//    catch (const SEMANTICANALYZER::SemanticError& error)
//    {
//        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
//    }
//}

//void SemanticAnalyzerTest::testGraph()
//{
//    AST::ASTTree ast(new AST::Node(PROGRAM));

//    auto programIt = ast.begin();

//    ast.insert(new AST::Node(START_GRAPH), programIt);
//    ast.insert(createGraphAST(), programIt);
//    ast.insert(new AST::Node(END_GRAPH), programIt);

//    SEMANTICANALYZER::AstStatementParser parser(ast);

//    auto programTree = parser.parse();
//    SEMANTICANALYZER::SemanticAnalyzer& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
//    analyzer.reset();

//    QVERIFY(programTree.size() == 1);
//    QVERIFY(programTree[0].first == GRAPH);

//    try
//    {
//        analyzer.semanticAnalysis(programTree, 1);
//    }
//    catch (const SEMANTICANALYZER::SemanticError& error)
//    {
//        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
//    }
//}

//void SemanticAnalyzerTest::testDotCloud()
//{
//    AST::ASTTree ast(new AST::Node(PROGRAM));

//    auto programIt = ast.begin();

//    ast.insert(new AST::Node(START_GRAPH), programIt);
//    ast.insert(createDotCloudAST(), programIt);
//    ast.insert(new AST::Node(END_GRAPH), programIt);

//    SEMANTICANALYZER::AstStatementParser parser(ast);

//    auto programTree = parser.parse();
//    SEMANTICANALYZER::SemanticAnalyzer& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
//    analyzer.reset();

//    QVERIFY(programTree.size() == 1);
//    QVERIFY(programTree[0].first == DOT_CLOUD);

//    try
//    {
//        analyzer.semanticAnalysis(programTree, 1);
//    }
//    catch (const SEMANTICANALYZER::SemanticError& error)
//    {
//        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
//    }
//}

QTEST_APPLESS_MAIN(SemanticAnalyzerTest)

#include "SemanticAnalyzerTest.moc"
