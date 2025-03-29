#include "AstStatementParser.h"


std::vector<std::pair<std::string, std::any>>& SEMANTICANALYZER::AstStatementParser::parse() noexcept
{
    for(auto it = astTree.begin(); it != astTree.end(); ++it)
    {
        std::cout << it->value << std::endl;

        std::pair<std::string, std::any> statement;

        if(it->value == OBJECT_DECL)
        {
            statement.first = OBJECT_DECL;
            statement.second = ObjectDecl();

            AST::ASTTree::DSFIterator objectIter(it.get());
            serializeObjectDec(objectIter, std::any_cast<ObjectDecl&>(statement.second));
        }
        else if(it->value == RELATION)
        {
            statement.first = RELATION;
            statement.second = Relation();

            AST::ASTTree::DSFIterator relationIter(it.get());
            serializeRelation(relationIter, std::any_cast<Relation&>(statement.second));
        }
        else if(it->value == NOTE)
        {
            statement.first = NOTE;
            statement.second = Note();

            AST::ASTTree::DSFIterator noteIter(it.get());
            serializeNote(noteIter, std::any_cast<Note&>(statement.second));
        }
        else if(it->value == GRAPH)
        {
            statement.first = GRAPH;
            statement.second = Graph();

            AST::ASTTree::DSFIterator graphIter(it.get());
            serializeGraph(graphIter, std::any_cast<Graph&>(statement.second));
        }
        else if(it->value == DOT_CLOUD)
        {
            statement.first = DOT_CLOUD;
            statement.second = DotCloud();

            AST::ASTTree::DSFIterator dotCloudIter(it.get());
            serializeDotCloud(dotCloudIter, std::any_cast<DotCloud&>(statement.second));
        }
        else continue;

        programTree.push_back(std::move(statement));
    }

    return programTree;
}


void SEMANTICANALYZER::AstStatementParser::serializeObjectDec(AST::ASTTree::DSFIterator& objectDecIter, ObjectDecl& objectDecl) noexcept
{
    for(auto it = objectDecIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == SHAPE)
        {
            ++it;
            objectDecl.shape = it->value;
        }
        else if(it->value == ID)
        {
            ++it;
            objectDecl.id = it->value;
        }
        else if(it->value == PROPERTY)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            objectDecl.properties.push_back(std::move(property));
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeRelation(AST::ASTTree::DSFIterator &relationIter, Relation &relation) noexcept
{
    for(auto it = relationIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == ID)
        {
            ++it;
            if(relation.id1.empty()) relation.id1 = it->value;
            else relation.id2 = it->value;
        }
        else if(it->value == ARROW)
        {
            ++it;
            relation.arrow = it->value;
        }
        else if(it->value == PROPERTY)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            relation.properties.push_back(std::move(property));
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeNote(AST::ASTTree::DSFIterator &noteIter, Note &note) noexcept
{
    for(auto it = noteIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == ID)
        {
            ++it;
            note.id = it->value;
        }
        else if(it->value == PROPERTY)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            note.properties.push_back(std::move(property));
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeGraph(AST::ASTTree::DSFIterator &graphIter, Graph &graph) noexcept
{
    bool startInternalBlock = false;

    for(auto it = graphIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == START_INTERNAL_BLOCK && startInternalBlock == false)
        {
            startInternalBlock = true;
            continue;
        }
        else if(it->value == ID)
        {
            ++it;
            graph.id = it->value;
        }
        else if(it->value == PROPERTY && startInternalBlock == false)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            graph.properties.push_back(property);
        }
        else if(it->value == OBJECT_DECL)
        {
            ObjectDecl objectDecl;
            AST::ASTTree::DSFIterator objectDeclIter(it.get());

            serializeObjectDec(objectDeclIter, objectDecl);
            graph.objects.push_back(std::move(objectDecl));
        }
        else if(it->value == RELATION)
        {
            Relation relation;
            AST::ASTTree::DSFIterator relationIter(it.get());

            serializeRelation(relationIter, relation);
            graph.relations.push_back(std::move(relation));
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeDotCloud(AST::ASTTree::DSFIterator &dotCloudIter, DotCloud &dotCloud) noexcept
{
    bool startInternalBlock = false;

    for(auto it = dotCloudIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == START_INTERNAL_BLOCK && startInternalBlock == false)
        {
            startInternalBlock = true;
            continue;
        }
        if(it->value == PROPERTY && startInternalBlock == false)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            dotCloud.externalProperties.push_back(std::move(property));
        }
        if(it->value == START_DOT_BLOCK)
        {
            Dot dot;

            while(it->value != END_DOT_BLOCK)
            {
                if(it->value == PROPERTY)
                {
                    Property property;
                    AST::ASTTree::DSFIterator proppertyIter(it.get());

                    serializeProperty(proppertyIter, property);
                    dot.internalProperties.push_back(std::move(property));
                }

                ++it;
            }

            dotCloud.dots.push_back(std::move(dot));
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeProperty(AST::ASTTree::DSFIterator &propertyIter, Property &property) noexcept
{
    for(auto it = propertyIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == PROPERTY_KEY)
        {
            ++it;
            property.key = it->value;
        }
        else if(it->value == TEXT || it->value == NUMBER)
        {
            ++it;
            property.value = it->value;
        }
    }
}


