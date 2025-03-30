#include <QtTest>

#include <iostream>
#include <memory>
#include <string_view>
#include <optional>

#include "SemanticAnalyzer.h"
#include "AstStatementParser.h"

#define CI_SYSTEM "CI"
#define DOT "dot"


class SemanticAnalyzerTest : public QObject
{
    Q_OBJECT

public:
    SemanticAnalyzerTest() = default;
    ~SemanticAnalyzerTest() = default;

private slots:
    void testGraph();
    void testDotCloud();

    /*
    void testObjectDecl();
    void testRelation();
    void testNote(); */

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
                AST::Node* object_decl = createObjectDeclAST(objectDecl);
                graph->addChild(object_decl->childNodes.front());
                object_decl->destroy();
            }

            for(auto& relation : strGraph.relations)
            {
                AST::Node* rel = createRelationAST(relation);
                graph->addChild(rel->childNodes.front());
                rel->destroy();
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

                _dot->destroy();
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

/*
void SemanticAnalyzerTest::testObjectDecl()
{
    AST::ASTTree ast(new AST::Node(PROGRAM));
    auto programIt = ast.begin();

    ast.insert(new AST::Node(START_GRAPH), programIt);

    SEMANTICANALYZER::ObjectDecl inputObject;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        inputObject.id = "rect";
        inputObject.shape = "rectangle";
    }
    else
    {
        std::cout << "=== Testing Object Declaration ===" << std::endl;
        std::cout << "Let's create an object together!" << std::endl;

        std::cout << "1. What would you like to name your object? (Enter an ID): ";
        std::cin >> inputObject.id;

        std::cout << "2. What shape should your object have? (e.g., circle, rectangle): ";
        std::cin >> inputObject.shape;

        std::cout << "3. How many properties would you like to add to your object? (Enter a number): ";
        std::size_t numberOfProperties{};

        if (std::cin >> numberOfProperties)
        {
            for(std::size_t i = 0; i < numberOfProperties; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "\nProperty #" << (i + 1) << ":" << std::endl;
                std::cout << "   - Enter the key for this property: ";
                std::cin >> property.key;

                std::cout << "   - Enter the value for this property: ";
                std::cin >> property.value;

                inputObject.properties.push_back(std::move(property));
            }
        }
        std::cout << "Great! Your object has been created." << std::endl;
    }

    ast.insert(createObjectDeclAST(inputObject), programIt);
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

    QVERIFY2(programTree.size() == 1,
             ("Expected program tree to contain exactly 1 statement, but found "
              + std::to_string(programTree.size())).c_str());
    QVERIFY2(programTree[0].first == OBJECT_DECL,
            "Expected first element to be an OBJECT_DECL, but it was not");

    SEMANTICANALYZER::ObjectDecl resultingObject = std::any_cast<SEMANTICANALYZER::ObjectDecl&>(programTree[0].second);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);

        QVERIFY2(resultingObject.id == inputObject.id, "Object IDs do not match");
        QVERIFY2(resultingObject.shape == inputObject.shape, "Object shapes do not match");
        QVERIFY2(resultingObject.properties.size() == inputObject.properties.size(), "Number of properties does not match");

        for (std::size_t i = 0; i < resultingObject.properties.size(); ++i)
        {
            QVERIFY2(resultingObject.properties[i].key == inputObject.properties[i].key,
                     ("Property key mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingObject.properties[i].value == inputObject.properties[i].value,
                     ("Property value mismatch at index " + std::to_string(i)).c_str());
        }

        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Object Successfully Processed!" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "ID: " << resultingObject.id << std::endl;
        std::cout << "Shape: " << resultingObject.shape << std::endl;
        std::cout << "Properties:" << std::endl;

        if (resultingObject.properties.empty())
        {
            std::cout << "   (No properties defined)" << std::endl;
        }
        else
        {
            for (std::size_t i = 0; i < resultingObject.properties.size(); ++i)
            {
                std::cout << "   " << (i + 1) << ". " << resultingObject.properties[i].key
                          << ": " << resultingObject.properties[i].value << std::endl;
            }
        }
        std::cout << "----------------------------------------" << std::endl;
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

    SEMANTICANALYZER::Relation inputRelation;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        inputRelation.id1 = "rect1";
        inputRelation.arrow = "->";
        inputRelation.id2 = "rect2";
    }
    else
    {
        std::cout << "=== Testing Relation Declaration ===" << std::endl;
        std::cout << "Let's define a relation between two objects!" << std::endl;

        std::cout << "1. What is the ID of the first object? (Enter ID1): ";
        std::cin >> inputRelation.id1;

        std::cout << "2. What is the ID of the second object? (Enter ID2): ";
        std::cin >> inputRelation.id2;

        std::cout << "3. What arrow connects them? (e.g., ->, --, =>): ";
        std::cin >> inputRelation.arrow;

        std::cout << "4. How many properties would you like to add to this relation? (Enter a number): ";
        std::size_t numberOfProperties{};

        if (std::cin >> numberOfProperties)
        {
            for(std::size_t i = 0; i < numberOfProperties; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "\nProperty #" << (i + 1) << ":" << std::endl;
                std::cout << "   - Enter the key for this property: ";
                std::cin >> property.key;

                std::cout << "   - Enter the value for this property: ";
                std::cin >> property.value;

                inputRelation.properties.push_back(std::move(property));
            }
        }
        std::cout << "Great! Your relation has been created." << std::endl;
    }

    ast.insert(createRelationAST(inputRelation), programIt);
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

    QVERIFY2(programTree.size() == 1,
             ("Expected program tree to contain exactly 1 statement, but found "
              + std::to_string(programTree.size())).c_str());
    QVERIFY2(programTree[0].first == RELATION,
            "Expected first element to be a RELATION, but it was not");

    SEMANTICANALYZER::Relation resultingRelation = std::any_cast<SEMANTICANALYZER::Relation&>(programTree[0].second);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);

        QVERIFY2(resultingRelation.id1 == inputRelation.id1, "First object IDs do not match");
        QVERIFY2(resultingRelation.id2 == inputRelation.id2, "Second object IDs do not match");
        QVERIFY2(resultingRelation.arrow == inputRelation.arrow, "Arrow types do not match");
        QVERIFY2(resultingRelation.properties.size() == inputRelation.properties.size(), "Number of properties does not match");

        for (std::size_t i = 0; i < resultingRelation.properties.size(); ++i)
        {
            QVERIFY2(resultingRelation.properties[i].key == inputRelation.properties[i].key,
                     ("Property key mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingRelation.properties[i].value == inputRelation.properties[i].value,
                     ("Property value mismatch at index " + std::to_string(i)).c_str());
        }

        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Relation Successfully Processed!" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "First Object ID: " << resultingRelation.id1 << std::endl;
        std::cout << "Arrow: " << resultingRelation.arrow << std::endl;
        std::cout << "Second Object ID: " << resultingRelation.id2 << std::endl;
        std::cout << "Properties:" << std::endl;

        if (resultingRelation.properties.empty())
        {
            std::cout << "   (No properties defined)" << std::endl;
        }
        else
        {
            for (std::size_t i = 0; i < resultingRelation.properties.size(); ++i)
            {
                std::cout << "   " << (i + 1) << ". " << resultingRelation.properties[i].key
                          << ": " << resultingRelation.properties[i].value << std::endl;
            }
        }
        std::cout << "----------------------------------------" << std::endl;
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

    SEMANTICANALYZER::Note inputNote;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        inputNote.id = "rect";
    }
    else
    {
        std::cout << "=== Testing Note Declaration ===" << std::endl;
        std::cout << "Let's create a note together!" << std::endl;

        std::cout << "1. What would you like to name your note? (Enter an ID): ";
        std::cin >> inputNote.id;

        std::cout << "2. How many properties would you like to add to your note? (Enter a number): ";
        std::size_t numberOfProperties{};

        if (std::cin >> numberOfProperties)
        {
            for(std::size_t i = 0; i < numberOfProperties; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "\nProperty #" << (i + 1) << ":" << std::endl;
                std::cout << "   - Enter the key for this property: ";
                std::cin >> property.key;

                std::cout << "   - Enter the value for this property: ";
                std::cin >> property.value;

                inputNote.properties.push_back(std::move(property));
            }
        }
        std::cout << "Great! Your note has been created." << std::endl;
    }

    ast.insert(createNoteAST(inputNote), programIt);
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

    QVERIFY2(programTree.size() == 1,
             ("Expected program tree to contain exactly 1 statement, but found "
              + std::to_string(programTree.size())).c_str());
    QVERIFY2(programTree[0].first == NOTE,
            "Expected first element to be a NOTE, but it was not");

    SEMANTICANALYZER::Note resultingNote = std::any_cast<SEMANTICANALYZER::Note&>(programTree[0].second);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);

        QVERIFY2(resultingNote.id == inputNote.id, "Note IDs do not match");
        QVERIFY2(resultingNote.properties.size() == inputNote.properties.size(), "Number of properties does not match");

        for (std::size_t i = 0; i < resultingNote.properties.size(); ++i)
        {
            QVERIFY2(resultingNote.properties[i].key == inputNote.properties[i].key,
                     ("Property key mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingNote.properties[i].value == inputNote.properties[i].value,
                     ("Property value mismatch at index " + std::to_string(i)).c_str());
        }

        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Note Successfully Processed!" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "ID: " << resultingNote.id << std::endl;
        std::cout << "Properties:" << std::endl;

        if (resultingNote.properties.empty())
        {
            std::cout << "   (No properties defined)" << std::endl;
        }
        else
        {
            for (std::size_t i = 0; i < resultingNote.properties.size(); ++i)
            {
                std::cout << "   " << (i + 1) << ". " << resultingNote.properties[i].key
                          << ": " << resultingNote.properties[i].value << std::endl;
            }
        }
        std::cout << "----------------------------------------" << std::endl;
    }
    catch (const SEMANTICANALYZER::SemanticError& error)
    {
        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}
*/


void SemanticAnalyzerTest::testGraph()
{
    AST::ASTTree ast(new AST::Node(PROGRAM));
    auto programIt = ast.begin();

    ast.insert(new AST::Node(START_GRAPH), programIt);

    SEMANTICANALYZER::Graph inputGraph;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        inputGraph.id = "my_graph";
    }
    else
    {
        std::cout << "=== Testing Graph Declaration ===" << std::endl;
        std::cout << "Let's build a graph together!" << std::endl;

        std::cout << "1. What would you like to name your graph? (Enter an ID): ";
        std::cin >> inputGraph.id;

        std::cout << "2. How many properties would you like to add to your graph? (Enter a number): ";
        std::size_t numberOfGraphProperties{};

        if (std::cin >> numberOfGraphProperties)
        {
            for(std::size_t i = 0; i < numberOfGraphProperties; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "\nGraph Property #" << (i + 1) << ":" << std::endl;
                std::cout << "   - Enter the key for this property: ";
                std::cin >> property.key;

                std::cout << "   - Enter the value for this property: ";
                std::cin >> property.value;

                inputGraph.properties.push_back(std::move(property));
            }
        }

        std::cout << "3. How many objects would you like to add to your graph? (Enter a number): ";
        std::size_t numberOfObjects{};

        if (std::cin >> numberOfObjects)
        {
            for(std::size_t i = 0; i < numberOfObjects; ++i)
            {
                SEMANTICANALYZER::ObjectDecl objectDecl;
                std::cout << "\nObject #" << (i + 1) << ":" << std::endl;
                std::cout << "   - What is the ID for this object? ";
                std::cin >> objectDecl.id;

                std::cout << "   - What shape should this object have? (e.g., circle, rectangle): ";
                std::cin >> objectDecl.shape;

                std::cout << "   - How many properties would you like to add to this object? (Enter a number): ";
                std::size_t numberOfObjectProperties{};

                if (std::cin >> numberOfObjectProperties)
                {
                    for(std::size_t j = 0; j < numberOfObjectProperties; ++j)
                    {
                        SEMANTICANALYZER::Property property;
                        std::cout << "     Property #" << (j + 1) << ":" << std::endl;
                        std::cout << "       - Enter the key for this property: ";
                        std::cin >> property.key;

                        std::cout << "       - Enter the value for this property: ";
                        std::cin >> property.value;

                        objectDecl.properties.push_back(std::move(property));
                    }
                }

                inputGraph.objects.push_back(std::move(objectDecl));
            }
        }

        std::cout << "4. How many relations would you like to add to your graph? (Enter a number): ";
        std::size_t numberOfRelations{};

        if (std::cin >> numberOfRelations)
        {
            for(std::size_t i = 0; i < numberOfRelations; ++i)
            {
                SEMANTICANALYZER::Relation relation;
                std::cout << "\nRelation #" << (i + 1) <<":" << std::endl;
                std::cout << "   - What is the ID of the first object? (Enter ID1): ";
                std::cin >> relation.id1;

                std::cout << "   - What is the ID of the second object? (Enter ID2): ";
                std::cin >> relation.id2;

                std::cout << "   - What arrow connects them? (e.g., ->, --, =>): ";
                std::cin >> relation.arrow;

                std::cout << "   - How many properties would you like to add to this relation? (Enter a number): ";
                std::size_t numberOfRelationProperties{};

                if (std::cin >> numberOfRelationProperties)
                {
                    for(std::size_t j = 0; j < numberOfRelationProperties; ++j)
                    {
                        SEMANTICANALYZER::Property property;
                        std::cout << "     Property #" << (j + 1) << ":" << std::endl;
                        std::cout << "       - Enter the key for this property: ";
                        std::cin >> property.key;

                        std::cout << "       - Enter the value for this property: ";
                        std::cin >> property.value;

                        relation.properties.push_back(std::move(property));
                    }
                }

                inputGraph.relations.push_back(std::move(relation));
            }
        }
        std::cout << "Great! Your graph has been created." << std::endl;
    }

    ast.insert(createGraphAST(inputGraph), programIt);
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

    QVERIFY2(programTree.size() == 1,
             ("Expected program tree to contain exactly 1 statement, but found "
              + std::to_string(programTree.size())).c_str());
    QVERIFY2(programTree[0].first == GRAPH,
            "Expected first element to be a GRAPH, but it was not");

    SEMANTICANALYZER::Graph resultingGraph = std::any_cast<SEMANTICANALYZER::Graph&>(programTree[0].second);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);

        QVERIFY2(resultingGraph.id == inputGraph.id, "Graph IDs do not match");
        QVERIFY2(resultingGraph.properties.size() == inputGraph.properties.size(), "Number of graph properties does not match");

        for (std::size_t i = 0; i < resultingGraph.properties.size(); ++i)
        {
            QVERIFY2(resultingGraph.properties[i].key == inputGraph.properties[i].key,
                     ("Graph property key mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingGraph.properties[i].value == inputGraph.properties[i].value,
                     ("Graph property value mismatch at index " + std::to_string(i)).c_str());
        }

        QVERIFY2(resultingGraph.objects.size() == inputGraph.objects.size(), "Number of objects does not match");

        for (std::size_t i = 0; i < resultingGraph.objects.size(); ++i)
        {
            QVERIFY2(resultingGraph.objects[i].id == inputGraph.objects[i].id,
                     ("Object ID mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingGraph.objects[i].shape == inputGraph.objects[i].shape,
                     ("Object shape mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingGraph.objects[i].properties.size() == inputGraph.objects[i].properties.size(),
                     ("Object properties size mismatch at index " + std::to_string(i)).c_str());
            for (std::size_t j = 0; j < resultingGraph.objects[i].properties.size(); ++j)
            {
                QVERIFY2(resultingGraph.objects[i].properties[j].key == inputGraph.objects[i].properties[j].key,
                         ("Object property key mismatch at object " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
                QVERIFY2(resultingGraph.objects[i].properties[j].value == inputGraph.objects[i].properties[j].value,
                         ("Object property value mismatch at object " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
            }
        }

        QVERIFY2(resultingGraph.relations.size() == inputGraph.relations.size(), "Number of relations does not match");

        for (std::size_t i = 0; i < resultingGraph.relations.size(); ++i)
        {
            QVERIFY2(resultingGraph.relations[i].id1 == inputGraph.relations[i].id1,
                     ("Relation ID1 mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingGraph.relations[i].id2 == inputGraph.relations[i].id2,
                     ("Relation ID2 mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingGraph.relations[i].arrow == inputGraph.relations[i].arrow,
                     ("Relation arrow mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingGraph.relations[i].properties.size() == inputGraph.relations[i].properties.size(),
                     ("Relation properties size mismatch at index " + std::to_string(i)).c_str());
            for (std::size_t j = 0; j < resultingGraph.relations[i].properties.size(); ++j)
            {
                QVERIFY2(resultingGraph.relations[i].properties[j].key == inputGraph.relations[i].properties[j].key,
                         ("Relation property key mismatch at relation " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
                QVERIFY2(resultingGraph.relations[i].properties[j].value == inputGraph.relations[i].properties[j].value,
                         ("Relation property value mismatch at relation " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
            }
        }

        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Graph Successfully Processed!" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Graph ID: " << resultingGraph.id << std::endl;

        std::cout << "Graph Properties:" << std::endl;
        if (resultingGraph.properties.empty())
        {
            std::cout << "   (No graph properties defined)" << std::endl;
        }
        else
        {
            for (std::size_t i = 0; i < resultingGraph.properties.size(); ++i)
            {
                std::cout << "   " << (i + 1) << ". " << resultingGraph.properties[i].key
                          << ": " << resultingGraph.properties[i].value << std::endl;
            }
        }

        std::cout << "Objects:" << std::endl;
        if (resultingGraph.objects.empty())
        {
            std::cout << "   (No objects defined)" << std::endl;
        }
        else
        {
            for (std::size_t i = 0; i < resultingGraph.objects.size(); ++i)
            {
                std::cout << "   Object #" << (i + 1) << ":" << std::endl;
                std::cout << "     ID: " << resultingGraph.objects[i].id << std::endl;
                std::cout << "     Shape: " << resultingGraph.objects[i].shape << std::endl;
                std::cout << "     Properties:" << std::endl;
                if (resultingGraph.objects[i].properties.empty())
                {
                    std::cout << "       (No properties defined)" << std::endl;
                }
                else
                {
                    for (std::size_t j = 0; j < resultingGraph.objects[i].properties.size(); ++j)
                    {
                        std::cout << "       " << (j + 1) << ". " << resultingGraph.objects[i].properties[j].key
                                  << ": " << resultingGraph.objects[i].properties[j].value << std::endl;
                    }
                }
            }
        }

        std::cout << "Relations:" << std::endl;
        if (resultingGraph.relations.empty())
        {
            std::cout << "   (No relations defined)" << std::endl;
        }
        else
        {
            for (std::size_t i = 0; i < resultingGraph.relations.size(); ++i)
            {
                std::cout << "   Relation #" << (i + 1) << ":" << std::endl;
                std::cout << "     First Object ID: " << resultingGraph.relations[i].id1 << std::endl;
                std::cout << "     Arrow: " << resultingGraph.relations[i].arrow << std::endl;
                std::cout << "     Second Object ID: " << resultingGraph.relations[i].id2 << std::endl;
                std::cout << "     Properties:" << std::endl;
                if (resultingGraph.relations[i].properties.empty())
                {
                    std::cout << "       (No properties defined)" << std::endl;
                }
                else
                {
                    for (std::size_t j = 0; j < resultingGraph.relations[i].properties.size(); ++j)
                    {
                        std::cout << "       " << (j + 1) << ". " << resultingGraph.relations[i].properties[j].key
                                  << ": " << resultingGraph.relations[i].properties[j].value << std::endl;
                    }
                }
            }
        }
        std::cout << "----------------------------------------" << std::endl;
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

    SEMANTICANALYZER::DotCloud inputDotCloud;

    const auto* ciEnv = std::getenv(CI_SYSTEM);
    const std::string_view ciFlag = ciEnv ? std::string_view(ciEnv) : std::string_view{};

    if (ciEnv && ciFlag == "true")
    {
        inputDotCloud.id = "dot_cloud";
    }
    else
    {
        std::cout << "=== Testing Dot Cloud Declaration ===" << std::endl;
        std::cout << "Let's create a dot cloud together!" << std::endl;

        std::cout << "1. What would you like to name your dot cloud? (Enter an ID): ";
        std::cin >> inputDotCloud.id;

        std::cout << "2. How many external properties would you like to add to your dot cloud? (Enter a number): ";
        std::size_t numberOfExternalProperties{};

        if (std::cin >> numberOfExternalProperties)
        {
            for(std::size_t i = 0; i < numberOfExternalProperties; ++i)
            {
                SEMANTICANALYZER::Property property;
                std::cout << "\nExternal Property #" << (i + 1) << ":" << std::endl;
                std::cout << "   - Enter the key for this property: ";
                std::cin >> property.key;

                std::cout << "   - Enter the value for this property: ";
                std::cin >> property.value;

                inputDotCloud.externalProperties.push_back(std::move(property));
            }
        }

        std::cout << "3. How many dots would you like to add to your dot cloud? (Enter a number): ";
        std::size_t numberOfDots{};

        if (std::cin >> numberOfDots)
        {
            for(std::size_t i = 0; i < numberOfDots; ++i)
            {
                SEMANTICANALYZER::Dot dot;
                std::cout << "\nDot #" << (i + 1) << ":" << std::endl;

                std::cout << "   - How many internal properties would you like to add to this dot? (Enter a number): ";
                std::size_t numberOfInternalProperties{};

                if (std::cin >> numberOfInternalProperties)
                {
                    for(std::size_t j = 0; j < numberOfInternalProperties; ++j)
                    {
                        SEMANTICANALYZER::Property property;
                        std::cout << "     Internal Property #" << (j + 1) << ":" << std::endl;
                        std::cout << "       - Enter the key for this property: ";
                        std::cin >> property.key;

                        std::cout << "       - Enter the value for this property: ";
                        std::cin >> property.value;

                        dot.internalProperties.push_back(std::move(property));
                    }
                }

                inputDotCloud.dots.push_back(std::move(dot));
            }
        }
        std::cout << "Great! Your dot cloud has been created." << std::endl;
    }

    ast.insert(createDotCloudAST(inputDotCloud), programIt);
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

    QVERIFY2(programTree.size() == 1,
             ("Expected program tree to contain exactly 1 statement, but found "
              + std::to_string(programTree.size())).c_str());
    QVERIFY2(programTree[0].first == DOT_CLOUD,
            "Expected first element to be a DOT_CLOUD, but it was not");

    SEMANTICANALYZER::DotCloud resultingDotCloud = std::any_cast<SEMANTICANALYZER::DotCloud&>(programTree[0].second);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);

        QVERIFY2(resultingDotCloud.id == inputDotCloud.id, "Dot cloud IDs do not match");
        QVERIFY2(resultingDotCloud.externalProperties.size() == inputDotCloud.externalProperties.size(),
                 "Number of external properties does not match");

        for (std::size_t i = 0; i < resultingDotCloud.externalProperties.size(); ++i)
        {
            QVERIFY2(resultingDotCloud.externalProperties[i].key == inputDotCloud.externalProperties[i].key,
                     ("External property key mismatch at index " + std::to_string(i)).c_str());
            QVERIFY2(resultingDotCloud.externalProperties[i].value == inputDotCloud.externalProperties[i].value,
                     ("External property value mismatch at index " + std::to_string(i)).c_str());
        }

        QVERIFY2(resultingDotCloud.dots.size() == inputDotCloud.dots.size(), "Number of dots does not match");

        for (std::size_t i = 0; i < resultingDotCloud.dots.size(); ++i)
        {
            QVERIFY2(resultingDotCloud.dots[i].internalProperties.size() == inputDotCloud.dots[i].internalProperties.size(),
                     ("Internal properties size mismatch at dot index " + std::to_string(i)).c_str());
            for (std::size_t j = 0; j < resultingDotCloud.dots[i].internalProperties.size(); ++j)
            {
                QVERIFY2(resultingDotCloud.dots[i].internalProperties[j].key == inputDotCloud.dots[i].internalProperties[j].key,
                         ("Internal property key mismatch at dot " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
                QVERIFY2(resultingDotCloud.dots[i].internalProperties[j].value == inputDotCloud.dots[i].internalProperties[j].value,
                         ("Internal property value mismatch at dot " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
            }
        }

        std::cout << "\n=== Test Results ===" << std::endl;
        std::cout << "Dot Cloud Successfully Processed!" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Dot Cloud ID: " << resultingDotCloud.id << std::endl;

        std::cout << "External Properties:" << std::endl;
        if (resultingDotCloud.externalProperties.empty())
        {
            std::cout << "   (No external properties defined)" << std::endl;
        }
        else
        {
            for (std::size_t i = 0; i < resultingDotCloud.externalProperties.size(); ++i)
            {
                std::cout << "   " << (i + 1) << ". " << resultingDotCloud.externalProperties[i].key
                          << ": " << resultingDotCloud.externalProperties[i].value << std::endl;
            }
        }

        std::cout << "Dots:" << std::endl;
        if (resultingDotCloud.dots.empty())
        {
            std::cout << "   (No dots defined)" << std::endl;
        }
        else
        {
            for (std::size_t i = 0; i < resultingDotCloud.dots.size(); ++i)
            {
                std::cout << "   Dot #" << (i + 1) << ":" << std::endl;
                std::cout << "     Internal Properties:" << std::endl;
                if (resultingDotCloud.dots[i].internalProperties.empty())
                {
                    std::cout << "       (No internal properties defined)" << std::endl;
                }
                else
                {
                    for (std::size_t j = 0; j < resultingDotCloud.dots[i].internalProperties.size(); ++j)
                    {
                        std::cout << "       " << (j + 1) << ". " << resultingDotCloud.dots[i].internalProperties[j].key
                                  << ": " << resultingDotCloud.dots[i].internalProperties[j].value << std::endl;
                    }
                }
            }
        }
        std::cout << "----------------------------------------" << std::endl;
    }
    catch (const SEMANTICANALYZER::SemanticError& error)
    {
        QFAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}


QTEST_APPLESS_MAIN(SemanticAnalyzerTest)

#include "SemanticAnalyzerTest.moc"
