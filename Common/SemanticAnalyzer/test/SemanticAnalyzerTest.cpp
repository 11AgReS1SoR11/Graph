#include <QtTest>

#include <iostream>
#include <memory>
#include <string_view>
#include <optional>

#include "SemanticAnalyzer.h"
#include "AstStatementParser.h"

#define CI_SYSTEM "CI"

class SemanticAnalyzerTest : public QObject
{
    Q_OBJECT

public:
    SemanticAnalyzerTest() = default;
    ~SemanticAnalyzerTest() = default;

private slots:
    void testObjectDecl();
    void testRelation();
    void testNote();
    void testGraph();
    void testDotCloud();

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
                AST::Node* _dot = createDotAST(dot);

                for(auto& child : _dot->childNodes)
                {
                    dot_cloud->addChild(child);
                }
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

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        objectDecl.id = "rect";
        objectDecl.shape = "rectangle";
    }
    else
    {
        std::cout << "TEST OBJECT_DECL: " << std::endl;

        std::cout << "Please enter an id of object: ";
        std::cin >> objectDecl.id;

        std::cout << "Please enter a shape of object: ";
        std::cin >> objectDecl.shape;

        std::cout << "Please enter a number of properties: ";
        std::size_t numberProp{};

        if (std::cin >> numberProp)
        {
            for(std::size_t i = 0; i < numberProp; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "Please enter a key of property number " << (i + 1) << ": ";
                std::cin >> property.key;

                std::cout << "Please enter a value of property number " << (i + 1) << ": ";
                std::cin >> property.value;

                objectDecl.properties.push_back(std::move(property));
            }
        }
    }

    ast.insert(createObjectDeclAST(objectDecl), programIt);
    ast.insert(new AST::Node(END_GRAPH), programIt);

#ifdef DEBUG
    for(auto it = ast.begin(); it != ast.end(); ++it)
    {
        std::cout << it.get()->value << std::endl;
    }
#endif

    SEMANTICANALYZER::AstStatementParser parser(ast);

    auto programTree = parser.parse();
    auto& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
    analyzer.reset();

    QVERIFY2(programTree.size() == 1, "Program tree size should be 1");
    QVERIFY2(programTree[0].first == OBJECT_DECL, "First element should be OBJECT_DECL");

    try
    {
        analyzer.semanticAnalysis(programTree, 1);
    }
    catch (const SEMANTICANALYZER::SemanticError& error)
    {
        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}


void SemanticAnalyzerTest::testRelation()
{
    AST::ASTTree ast(new AST::Node(PROGRAM));
    auto programIt = ast.begin();

    ast.insert(new AST::Node(START_GRAPH), programIt);

    SEMANTICANALYZER::Relation relation;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        relation.id1 = "rect1";
        relation.arrow = "->";
        relation.id2 = "rect2";
    }
    else
    {
        std::cout << "TEST RELATION: " << std::endl;

        std::cout << "Please enter an id1 of object: ";
        std::cin >> relation.id1;

        std::cout << "Please enter an id2 of object: ";
        std::cin >> relation.id2;

        std::cout << "Please enter an arrow: ";
        std::cin >> relation.arrow;

        std::cout << "Please enter a number of properties: ";
        std::size_t numberProp{};

        if (std::cin >> numberProp)
        {
            for(std::size_t i = 0; i < numberProp; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "Please enter a key of property number " << (i + 1) << ": ";
                std::cin >> property.key;

                std::cout << "Please enter a value of property number " << (i + 1) << ": ";
                std::cin >> property.value;

                relation.properties.push_back(std::move(property));
            }
        }
    }

    ast.insert(createRelationAST(relation), programIt);
    ast.insert(new AST::Node(END_GRAPH), programIt);

#ifdef DEBUG
    for(auto it = ast.begin(); it != ast.end(); ++it)
    {
        std::cout << it.get()->value << std::endl;
    }
#endif

    SEMANTICANALYZER::AstStatementParser parser(ast);

    auto programTree = parser.parse();
    auto& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
    analyzer.reset();

    QVERIFY2(programTree.size() == 1, "Program tree size should be 1");
    QVERIFY2(programTree[0].first == RELATION, "First element should be RELATION");

    try
    {
        analyzer.semanticAnalysis(programTree, 1);
    }
    catch (const SEMANTICANALYZER::SemanticError& error)
    {
        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}

void SemanticAnalyzerTest::testNote()
{
    AST::ASTTree ast(new AST::Node(PROGRAM));
    auto programIt = ast.begin();

    ast.insert(new AST::Node(START_GRAPH), programIt);

    SEMANTICANALYZER::Note note;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        note.id = "rect";
    }
    else
    {
        std::cout << "TEST NOTE: " << std::endl;

        std::cout << "Please enter an id of object: ";
        std::cin >> note.id;

        std::cout << "Please enter a number of properties: ";
        std::size_t numberProp{};

        if (std::cin >> numberProp)
        {
            for(std::size_t i = 0; i < numberProp; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "Please enter a key of property number " << (i + 1) << ": ";
                std::cin >> property.key;

                std::cout << "Please enter a value of property number " << (i + 1) << ": ";
                std::cin >> property.value;

                note.properties.push_back(std::move(property));
            }
        }
    }

    ast.insert(createNoteAST(note), programIt);
    ast.insert(new AST::Node(END_GRAPH), programIt);

#ifdef DEBUG
    for(auto it = ast.begin(); it != ast.end(); ++it)
    {
        std::cout << it.get()->value << std::endl;
    }
#endif

    SEMANTICANALYZER::AstStatementParser parser(ast);

    auto programTree = parser.parse();
    auto& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
    analyzer.reset();

    QVERIFY2(programTree.size() == 1, "Program tree size should be 1");
    QVERIFY2(programTree[0].first == NOTE, "First element should be NOTE");

    try
    {
        analyzer.semanticAnalysis(programTree, 1);
    }
    catch (const SEMANTICANALYZER::SemanticError& error)
    {
        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}

void SemanticAnalyzerTest::testGraph()
{
    AST::ASTTree ast(new AST::Node(PROGRAM));
    auto programIt = ast.begin();

    ast.insert(new AST::Node(START_GRAPH), programIt);

    SEMANTICANALYZER::Graph graph;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        graph.id = "graph";
    }
    else
    {
        std::cout << "TEST GRAPH: " << std::endl;

        std::cout << "Please enter an id of graph: ";
        std::cin >> graph.id;

        std::cout << "Please enter a number of properties of graph: ";
        std::size_t numberProp{};

        if (std::cin >> numberProp)
        {
            for(std::size_t i = 0; i < numberProp; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "Please enter a key of property number " << (i + 1) << ": ";
                std::cin >> property.key;

                std::cout << "Please enter a value of property number " << (i + 1) << ": ";
                std::cin >> property.value;

                graph.properties.push_back(std::move(property));
            }
        }

        std::cout << "Please enter a number of objects: ";
        std::size_t numberObj{};

        if (std::cin >> numberObj)
        {
            for(std::size_t i = 0; i < numberObj; ++i)
            {
                SEMANTICANALYZER::ObjectDecl objectDecl;

                std::cout << "Please enter an id of object number " << (i + 1) << ": ";
                std::cin >> objectDecl.id;

                std::cout << "Please enter a shape of object number " << (i + 1) << ": ";
                std::cin >> objectDecl.shape;

                std::cout << "Please enter a number of properties of object number " << (i + 1) << ": ";
                std::size_t numberProp{};

                if (std::cin >> numberProp)
                {
                    for(std::size_t i = 0; i < numberProp; ++i)
                    {
                        SEMANTICANALYZER::Property property;
                        std::cout << "Please enter a key of property number " << (i + 1) << ": ";
                        std::cin >> property.key;

                        std::cout << "Please enter a value of property number " << (i + 1) << ": ";
                        std::cin >> property.value;

                        objectDecl.properties.push_back(std::move(property));
                    }
                }

                graph.objects.push_back(std::move(objectDecl));
            }
        }

        std::cout << "Please enter a number of relations: ";
        std::size_t numberRel{};

        if (std::cin >> numberRel)
        {
            for(std::size_t i = 0; i < numberRel; ++i)
            {
                SEMANTICANALYZER::Relation relation;

                std::cout << "Please enter an id1 of object in relation number: " << (i + 1) << ": ";
                std::cin >> relation.id1;

                std::cout << "Please enter an id2 of object in relation number: " << (i + 1) << ": ";
                std::cin >> relation.id2;

                std::cout << "Please enter an arrow: ";
                std::cin >> relation.arrow;

                std::cout << "Please enter a number of properties of relation number " << (i + 1) << ": ";
                std::size_t numberProp{};

                if (std::cin >> numberProp)
                {
                    for(std::size_t i = 0; i < numberProp; ++i)
                    {
                        SEMANTICANALYZER::Property property;
                        std::cout << "Please enter a key of property number " << (i + 1) << ": ";
                        std::cin >> property.key;

                        std::cout << "Please enter a value of property number " << (i + 1) << ": ";
                        std::cin >> property.value;

                        relation.properties.push_back(std::move(property));
                    }
                }

                graph.relations.push_back(std::move(relation));
            }
        }
    }

    ast.insert(createGraphAST(graph), programIt);
    ast.insert(new AST::Node(END_GRAPH), programIt);

#ifdef DEBUG
    for(auto it = ast.begin(); it != ast.end(); ++it)
    {
        std::cout << it.get()->value << std::endl;
    }
#endif

    SEMANTICANALYZER::AstStatementParser parser(ast);

    auto programTree = parser.parse();
    auto& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
    analyzer.reset();

    QVERIFY2(programTree.size() == 1, "Program tree size should be 1");
    QVERIFY2(programTree[0].first == GRAPH, "First element should be GRAPH");

    try
    {
        analyzer.semanticAnalysis(programTree, 1);
    }
    catch (const SEMANTICANALYZER::SemanticError& error)
    {
        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}

void SemanticAnalyzerTest::testDotCloud()
{
    AST::ASTTree ast(new AST::Node(PROGRAM));
    auto programIt = ast.begin();

    ast.insert(new AST::Node(START_GRAPH), programIt);

    SEMANTICANALYZER::DotCloud dotCloud;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        dotCloud.id = "dot_cloud";
    }
    else
    {
        std::cout << "TEST DOT_CLOUD: " << std::endl;

        std::cout << "Please enter an id of dot_cloud: ";
        std::cin >> dotCloud.id;

        std::cout << "Please enter a number of properties of dot_cloud: ";
        std::size_t numberProp{};

        if (std::cin >> numberProp)
        {
            for(std::size_t i = 0; i < numberProp; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "Please enter a key of property number " << (i + 1) << ": ";
                std::cin >> property.key;

                std::cout << "Please enter a value of property number " << (i + 1) << ": ";
                std::cin >> property.value;

                dotCloud.externalProperties.push_back(std::move(property));
            }
        }

        std::cout << "Please enter a number of dots: ";
        std::size_t numberDot{};

        if (std::cin >> numberDot)
        {
            for(std::size_t i = 0; i < numberDot; ++i)
            {
                SEMANTICANALYZER::Dot dot;

                std::cout << "Please enter a number of properties of dot number " << (i + 1) << ": ";
                std::size_t numberProp{};

                if (std::cin >> numberProp)
                {
                    for(std::size_t i = 0; i < numberProp; ++i)
                    {
                        SEMANTICANALYZER::Property property;
                        std::cout << "Please enter a key of property number " << (i + 1) << ": ";
                        std::cin >> property.key;

                        std::cout << "Please enter a value of property number " << (i + 1) << ": ";
                        std::cin >> property.value;

                        dot.internalProperties.push_back(std::move(property));
                    }
                }

                dotCloud.dots.push_back(std::move(dot));
            }
        }
    }

    ast.insert(createDotCloudAST(dotCloud), programIt);
    ast.insert(new AST::Node(END_GRAPH), programIt);

#ifdef DEBUG
    for(auto it = ast.begin(); it != ast.end(); ++it)
    {
        std::cout << it.get()->value << std::endl;
    }
#endif

    SEMANTICANALYZER::AstStatementParser parser(ast);

    auto programTree = parser.parse();
    auto& analyzer = SEMANTICANALYZER::SemanticAnalyzer::getInstance();
    analyzer.reset();

    QVERIFY2(programTree.size() == 1, "Program tree size should be 1");
    QVERIFY2(programTree[0].first == DOT_CLOUD, "First element should be DOT_CLOUD");

    try
    {
        analyzer.semanticAnalysis(programTree, 1);
    }
    catch (const SEMANTICANALYZER::SemanticError& error)
    {
        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}

QTEST_APPLESS_MAIN(SemanticAnalyzerTest)

#include "SemanticAnalyzerTest.moc"
