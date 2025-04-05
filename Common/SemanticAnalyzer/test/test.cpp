#include <catch2/catch_test_macros.hpp>

#include "SemanticAnalyzer.hpp"
#include "AstStatementParser.hpp"

#include <iostream>

static constexpr auto CI_SYSTEM = "CI";
static constexpr auto DOT = "dot";

#define REQUIRE_MESSAGE(condition, message) {if (!(condition)) {FAIL(message);}}

AST::Node* createObjectDeclAST(SEMANTICANALYZER::ObjectDecl const& objectDecl);
AST::Node* createRelationAST(SEMANTICANALYZER::Relation const& relation);
AST::Node* createNoteAST(SEMANTICANALYZER::Note const& note);
AST::Node* createGraphAST(SEMANTICANALYZER::Graph const& graph);
AST::Node* createDotCloudAST(SEMANTICANALYZER::DotCloud const& dotCloud);
AST::Node* createPropertyAST(SEMANTICANALYZER::Property const& property);
AST::Node* createDotAST(SEMANTICANALYZER::Dot const& dot);


TEST_CASE("test object_decl semantic", "[SemanticAnalyzer]")
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

    for(auto it = ast.begin(); it != ast.end(); ++it)
    {
        std::cout << it.get()->value << std::endl;
    }

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

    REQUIRE_MESSAGE(programTree.size() == 1,
             ("Expected program tree to contain exactly 1 statement, but found "
              + std::to_string(programTree.size())).c_str());
    REQUIRE_MESSAGE(programTree[0].first == OBJECT_DECL,
            "Expected first element to be an OBJECT_DECL, but it was not");

    SEMANTICANALYZER::ObjectDecl resultingObject = std::any_cast<SEMANTICANALYZER::ObjectDecl&>(programTree[0].second);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);

        REQUIRE_MESSAGE(resultingObject.id == inputObject.id, "Object IDs do not match");
        REQUIRE_MESSAGE(resultingObject.shape == inputObject.shape, "Object shapes do not match");
        REQUIRE_MESSAGE(resultingObject.properties.size() == inputObject.properties.size(), "Number of properties does not match");

        for (std::size_t i = 0; i < resultingObject.properties.size(); ++i)
        {
            REQUIRE_MESSAGE(resultingObject.properties[i].key == inputObject.properties[i].key,
                     ("Property key mismatch at index " + std::to_string(i)).c_str());
            REQUIRE_MESSAGE(resultingObject.properties[i].value == inputObject.properties[i].value,
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
        FAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}


TEST_CASE("test graph semantic", "[SemanticAnalyzer]")
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

    REQUIRE_MESSAGE(programTree.size() == 1,
             ("Expected program tree to contain exactly 1 statement, but found "
              + std::to_string(programTree.size())).c_str());
    REQUIRE_MESSAGE(programTree[0].first == GRAPH,
            "Expected first element to be a GRAPH, but it was not");

    SEMANTICANALYZER::Graph resultingGraph = std::any_cast<SEMANTICANALYZER::Graph&>(programTree[0].second);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);

        REQUIRE_MESSAGE(resultingGraph.id == inputGraph.id, "Graph IDs do not match");
        REQUIRE_MESSAGE(resultingGraph.properties.size() == inputGraph.properties.size(), "Number of graph properties does not match");

        for (std::size_t i = 0; i < resultingGraph.properties.size(); ++i)
        {
            REQUIRE_MESSAGE(resultingGraph.properties[i].key == inputGraph.properties[i].key,
                     ("Graph property key mismatch at index " + std::to_string(i)).c_str());
            REQUIRE_MESSAGE(resultingGraph.properties[i].value == inputGraph.properties[i].value,
                     ("Graph property value mismatch at index " + std::to_string(i)).c_str());
        }

        REQUIRE_MESSAGE(resultingGraph.objects.size() == inputGraph.objects.size(), "Number of objects does not match");

        for (std::size_t i = 0; i < resultingGraph.objects.size(); ++i)
        {
            REQUIRE_MESSAGE(resultingGraph.objects[i].id == inputGraph.objects[i].id,
                     ("Object ID mismatch at index " + std::to_string(i)).c_str());
            REQUIRE_MESSAGE(resultingGraph.objects[i].shape == inputGraph.objects[i].shape,
                     ("Object shape mismatch at index " + std::to_string(i)).c_str());
            REQUIRE_MESSAGE(resultingGraph.objects[i].properties.size() == inputGraph.objects[i].properties.size(),
                     ("Object properties size mismatch at index " + std::to_string(i)).c_str());
            for (std::size_t j = 0; j < resultingGraph.objects[i].properties.size(); ++j)
            {
                REQUIRE_MESSAGE(resultingGraph.objects[i].properties[j].key == inputGraph.objects[i].properties[j].key,
                         ("Object property key mismatch at object " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
                REQUIRE_MESSAGE(resultingGraph.objects[i].properties[j].value == inputGraph.objects[i].properties[j].value,
                         ("Object property value mismatch at object " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
            }
        }

        REQUIRE_MESSAGE(resultingGraph.relations.size() == inputGraph.relations.size(), "Number of relations does not match");

        for (std::size_t i = 0; i < resultingGraph.relations.size(); ++i)
        {
            REQUIRE_MESSAGE(resultingGraph.relations[i].id1 == inputGraph.relations[i].id1,
                     ("Relation ID1 mismatch at index " + std::to_string(i)).c_str());
            REQUIRE_MESSAGE(resultingGraph.relations[i].id2 == inputGraph.relations[i].id2,
                     ("Relation ID2 mismatch at index " + std::to_string(i)).c_str());
            REQUIRE_MESSAGE(resultingGraph.relations[i].arrow == inputGraph.relations[i].arrow,
                     ("Relation arrow mismatch at index " + std::to_string(i)).c_str());
            REQUIRE_MESSAGE(resultingGraph.relations[i].properties.size() == inputGraph.relations[i].properties.size(),
                     ("Relation properties size mismatch at index " + std::to_string(i)).c_str());
            for (std::size_t j = 0; j < resultingGraph.relations[i].properties.size(); ++j)
            {
                REQUIRE_MESSAGE(resultingGraph.relations[i].properties[j].key == inputGraph.relations[i].properties[j].key,
                         ("Relation property key mismatch at relation " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
                REQUIRE_MESSAGE(resultingGraph.relations[i].properties[j].value == inputGraph.relations[i].properties[j].value,
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
        FAIL(("Unexpected exception: " + std::string(error.what())).c_str());
    }
}

TEST_CASE("test dot_cloud semantic", "[SemanticAnalyzer]")
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

    REQUIRE_MESSAGE(programTree.size() == 1,
             ("Expected program tree to contain exactly 1 statement, but found "
              + std::to_string(programTree.size())).c_str());
    REQUIRE_MESSAGE(programTree[0].first == DOT_CLOUD,
            "Expected first element to be a DOT_CLOUD, but it was not");

    SEMANTICANALYZER::DotCloud resultingDotCloud = std::any_cast<SEMANTICANALYZER::DotCloud&>(programTree[0].second);

    try
    {
        analyzer.semanticAnalysis(programTree, 1);

        REQUIRE_MESSAGE(resultingDotCloud.id == inputDotCloud.id, "Dot cloud IDs do not match");
        REQUIRE_MESSAGE(resultingDotCloud.externalProperties.size() == inputDotCloud.externalProperties.size(),
                 "Number of external properties does not match");

        for (std::size_t i = 0; i < resultingDotCloud.externalProperties.size(); ++i)
        {
            REQUIRE_MESSAGE(resultingDotCloud.externalProperties[i].key == inputDotCloud.externalProperties[i].key,
                     ("External property key mismatch at index " + std::to_string(i)).c_str());
            REQUIRE_MESSAGE(resultingDotCloud.externalProperties[i].value == inputDotCloud.externalProperties[i].value,
                     ("External property value mismatch at index " + std::to_string(i)).c_str());
        }

        REQUIRE_MESSAGE(resultingDotCloud.dots.size() == inputDotCloud.dots.size(), "Number of dots does not match");

        for (std::size_t i = 0; i < resultingDotCloud.dots.size(); ++i)
        {
            REQUIRE_MESSAGE(resultingDotCloud.dots[i].internalProperties.size() == inputDotCloud.dots[i].internalProperties.size(),
                     ("Internal properties size mismatch at dot index " + std::to_string(i)).c_str());
            for (std::size_t j = 0; j < resultingDotCloud.dots[i].internalProperties.size(); ++j)
            {
                REQUIRE_MESSAGE(resultingDotCloud.dots[i].internalProperties[j].key == inputDotCloud.dots[i].internalProperties[j].key,
                         ("Internal property key mismatch at dot " + std::to_string(i) + ", property " + std::to_string(j)).c_str());
                REQUIRE_MESSAGE(resultingDotCloud.dots[i].internalProperties[j].value == inputDotCloud.dots[i].internalProperties[j].value,
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
        FAIL("Unexpected exception: " + std::string(error.what()));
    }
}

AST::Node* createObjectDeclAST(SEMANTICANALYZER::ObjectDecl const& objectDecl)
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


AST::Node* createRelationAST(SEMANTICANALYZER::Relation const& rel)
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


AST::Node* createNoteAST(SEMANTICANALYZER::Note const& strNote)
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


AST::Node* createGraphAST(SEMANTICANALYZER::Graph const& strGraph)
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


AST::Node* createDotCloudAST(SEMANTICANALYZER::DotCloud const& dotCloud)
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


AST::Node* createPropertyAST(SEMANTICANALYZER::Property const& prop)
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


AST::Node* createDotAST(SEMANTICANALYZER::Dot const& strDot)
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
