﻿#include "AstStatementParser.hpp"


std::vector<std::pair<std::string, std::any>>& SEMANTICANALYZER::AstStatementParser::parse() noexcept
{
    for(astIter = astTree.begin(); astIter != astTree.end(); ++astIter)
    {

        std::pair<std::string, std::any> statement;

        if(astIter->value == GRAMMERCONSTANTS::OBJECT_DECL)
        {
            statement.first = GRAMMERCONSTANTS::OBJECT_DECL;
            statement.second = ObjectDecl();

            AST::ASTTree::DSFIterator objectIter(astIter.get());
            serializeObjectDec(objectIter, std::any_cast<ObjectDecl&>(statement.second));
        }
        else if(astIter->value == GRAMMERCONSTANTS::RELATION)
        {
            statement.first = GRAMMERCONSTANTS::RELATION;
            statement.second = Relation();

            AST::ASTTree::DSFIterator relationIter(astIter.get());
            serializeRelation(relationIter, std::any_cast<Relation&>(statement.second));
        }
        else if(astIter->value == GRAMMERCONSTANTS::NOTE)
        {
            statement.first = GRAMMERCONSTANTS::NOTE;
            statement.second = Note();

            AST::ASTTree::DSFIterator noteIter(astIter.get());
            serializeNote(noteIter, std::any_cast<Note&>(statement.second));
        }
        else if(astIter->value == GRAMMERCONSTANTS::GRAPH)
        {
            statement.first = GRAMMERCONSTANTS::GRAPH;
            statement.second = Graph();

            AST::ASTTree::DSFIterator graphIter(astIter.get());
            serializeGraph(graphIter, std::any_cast<Graph&>(statement.second));
        }
        else if(astIter->value == GRAMMERCONSTANTS::DOT_CLOUD)
        {
            statement.first = GRAMMERCONSTANTS::DOT_CLOUD;
            statement.second = DotCloud();

            AST::ASTTree::DSFIterator dotCloudIter(astIter.get());
            serializeDotCloud(dotCloudIter, std::any_cast<DotCloud&>(statement.second));
        }
        else continue;

        programTree.push_back(std::move(statement));
    }

    return programTree;
}


void SEMANTICANALYZER::AstStatementParser::serializeObjectDec(AST::ASTTree::DSFIterator& objectDecIter, ObjectDecl& objectDecl) noexcept
{
    for(auto& it = objectDecIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == GRAMMERCONSTANTS::SHAPE)
        {
            ++it;
            ++astIter;
            objectDecl.shape = it->value;
        }
        else if(it->value == GRAMMERCONSTANTS::ID)
        {
            ++it;
            ++astIter;
            objectDecl.id = it->value;
        }
        else if(it->value == GRAMMERCONSTANTS::PROPERTY)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            objectDecl.properties.push_back(std::move(property));

            while(it.get() != astIter.get()) {
                ++it;
            }
        }

        auto nextIt = it;
        ++nextIt;
        if(nextIt != AST::ASTTree::DSFIterator())
        {
            ++astIter;
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeRelation(AST::ASTTree::DSFIterator &relationIter, Relation &relation) noexcept
{
    for(auto& it = relationIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == GRAMMERCONSTANTS::ID)
        {
            ++it;
            ++astIter;
            if(relation.id1.empty()) relation.id1 = it->value;
            else relation.id2 = it->value;
        }
        else if(it->value == GRAMMERCONSTANTS::ARROW)
        {
            ++it;
            ++astIter;
            relation.arrow = it->value;
        }
        else if(it->value == GRAMMERCONSTANTS::PROPERTY)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            relation.properties.push_back(std::move(property));

            while(it.get() != astIter.get()) {
                ++it;
            }
        }

        auto nextIt = it;
        ++nextIt;
        if(nextIt != AST::ASTTree::DSFIterator())
        {
            ++astIter;
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeNote(AST::ASTTree::DSFIterator &noteIter, Note &note) noexcept
{
    for(auto& it = noteIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == GRAMMERCONSTANTS::ID)
        {
            ++it;
            ++astIter;
            note.id = it->value;
        }
        else if(it->value == GRAMMERCONSTANTS::PROPERTY)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            note.properties.push_back(std::move(property));

            while(it.get() != astIter.get()) {
                ++it;
            }
        }

        auto nextIt = it;
        ++nextIt;
        if(nextIt != AST::ASTTree::DSFIterator())
        {
            ++astIter;
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeGraph(AST::ASTTree::DSFIterator &graphIter, Graph &graph) noexcept
{
    bool startInternalBlock = false;

    for(auto& it = graphIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == GRAMMERCONSTANTS::START_INTERNAL_BLOCK && startInternalBlock == false)
        {
            startInternalBlock = true;
        }
        else if(it->value == GRAMMERCONSTANTS::ID)
        {
            ++it;
            ++astIter;
            graph.id = it->value;
        }
        else if(it->value == GRAMMERCONSTANTS::PROPERTY && startInternalBlock == false)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            graph.properties.push_back(property);

            while(it.get() != astIter.get()) {
                ++it;
            }

        }
        else if(it->value == GRAMMERCONSTANTS::OBJECT_DECL)
        {
            ObjectDecl objectDecl;
            AST::ASTTree::DSFIterator objectDeclIter(it.get());

            serializeObjectDec(objectDeclIter, objectDecl);
            graph.objects.push_back(std::move(objectDecl));

            while(it.get() != astIter.get()) {
                ++it;
            }
        }
        else if(it->value == GRAMMERCONSTANTS::RELATION)
        {
            Relation relation;
            AST::ASTTree::DSFIterator relationIter(it.get());

            serializeRelation(relationIter, relation);
            graph.relations.push_back(std::move(relation));

            while(it.get() != astIter.get()) {
                ++it;
            }
        }

        auto nextIt = it;
        ++nextIt;
        if(nextIt != AST::ASTTree::DSFIterator())
        {
            ++astIter;
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeDotCloud(AST::ASTTree::DSFIterator &dotCloudIter, DotCloud &dotCloud) noexcept
{
    bool startInternalBlock = false;

    for(auto& it = dotCloudIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == GRAMMERCONSTANTS::START_INTERNAL_BLOCK && startInternalBlock == false)
        {
            startInternalBlock = true;
        }
        else if(it->value == GRAMMERCONSTANTS::ID)
        {
            ++it;
            ++astIter;
            dotCloud.id = it->value;
        }
        else if(it->value == GRAMMERCONSTANTS::PROPERTY && startInternalBlock == false)
        {
            Property property;
            AST::ASTTree::DSFIterator propertyIter(it.get());

            serializeProperty(propertyIter, property);
            dotCloud.externalProperties.push_back(std::move(property));

            while(it.get() != astIter.get()) {
                ++it;
            }
        }
        else if(it->value == GRAMMERCONSTANTS::START_DOT_BLOCK)
        {
            Dot dot;

            while(it->value != GRAMMERCONSTANTS::END_DOT_BLOCK)
            {
                if(it->value == GRAMMERCONSTANTS::PROPERTY)
                {
                    Property property;
                    AST::ASTTree::DSFIterator propertyIter(it.get());

                    serializeProperty(propertyIter, property);
                    dot.internalProperties.push_back(std::move(property));

                    while(it.get() != astIter.get()) {
                        ++it;
                    }
                }

                ++it;
                ++astIter;
            }

            dotCloud.dots.push_back(std::move(dot));
        }

        auto nextIt = it;
        ++nextIt;
        if(nextIt != AST::ASTTree::DSFIterator())
        {
            ++astIter;
        }
    }
}


void SEMANTICANALYZER::AstStatementParser::serializeProperty(AST::ASTTree::DSFIterator &propertyIter, Property &property) noexcept
{
    for(auto& it = propertyIter; it != AST::ASTTree::DSFIterator(); ++it)
    {
        if(it->value == GRAMMERCONSTANTS::PROPERTY_KEY)
        {
            ++it;
            ++astIter;
            property.key = it->value;
        }
        else if(it->value == GRAMMERCONSTANTS::TEXT || it->value == GRAMMERCONSTANTS::NUMBER)
        {
            ++it;
            ++astIter;
            property.value = it->value;
        }

        auto nextIt = it;
        ++nextIt;
        if(nextIt != AST::ASTTree::DSFIterator())
        {
            ++astIter;
        }
    }
}


