#include "AstStatementParser.h"


std::vector<std::pair<std::string, std::any>>& SEMANTICANALYZER::AstStatementParser::parse()
{
    for(auto it = astTree.begin(); it != astTree.end(); ++it)
    {
        std::pair<std::string, std::any> statement;

        if(it->value == OBJECT_DECL)
        {
            statement.first = OBJECT_DECL;
            serializeObjectDec(it, std::any_cast<ObjectDecl&>(statement.second));
        }
        else if(it->value == RELATION)
        {
            statement.first = RELATION;
            serializeRelation(it, std::any_cast<Relation&>(statement.second));
        }
        else if(it->value == NOTE)
        {
            statement.first = NOTE;
            serializeNote(it, std::any_cast<Note&>(statement.second));
        }
        else if(it->value == GRAPH)
        {
            statement.first = GRAPH;
            serializeGraph(it, std::any_cast<Graph&>(statement.second));
        }
        else if(it->value == DOT_CLOUD)
        {
            statement.first = DOT_CLOUD;
            serializeDotCloud(it, std::any_cast<DotCloud&>(statement.second));
        }

        programTree.push_back(statement);
    }

    return programTree;
}


void SEMANTICANALYZER::AstStatementParser::serializeObjectDec(AST::ASTTree::DSFIterator& objectDecIter, ObjectDecl& objectDecl)
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
            serializeProperty(it, property);
            objectDecl.properties.push_back(property);
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeRelation(AST::ASTTree::DSFIterator &relationIter, Relation &relation)
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
            serializeProperty(it, property);
            relation.properties.push_back(property);
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeNote(AST::ASTTree::DSFIterator &noteIter, Note &note)
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
            serializeProperty(it, property);
            note.properties.push_back(property);
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeGraph(AST::ASTTree::DSFIterator &graphIter, Graph &graph)
{
    for(auto it = graphIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == ID)
        {
            ++it;
            graph.id = it->value;
        }
        else if(it->value == PROPERTY)
        {
            Property property;
            serializeProperty(it, property);
            graph.properties.push_back(property);
        }
        else if(it->value == OBJECT_DECL)
        {
            ObjectDecl objectDecl;
            serializeObjectDec(it, objectDecl);
            graph.objects.push_back(objectDecl);
        }
        else if(it->value == RELATION)
        {
            Relation relation;
            serializeRelation(it, relation);
            graph.relations.push_back(relation);
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeDotCloud(AST::ASTTree::DSFIterator &dotCloudIter, DotCloud &dotCloud)
{
    bool startInternalBlock = false;

    for(auto it = dotCloudIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == START_INTERNAL_BLOCK)
        {
            startInternalBlock = true;
        }
        if(it->value == PROPERTY && startInternalBlock == false)
        {
            Property property;
            serializeProperty(it, property);
            dotCloud.externalProperties.push_back(property);
        }
        if(it->value == PROPERTY && startInternalBlock == true)
        {
            Property property;
            serializeProperty(it, property);
            dotCloud.internalProperties.push_back(property);
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeProperty(AST::ASTTree::DSFIterator &propertyIter, Property &property)
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


