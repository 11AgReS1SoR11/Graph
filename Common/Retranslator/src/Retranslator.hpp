#include <memory>
#include "AST.hpp"
#include <map>
#include "Shape.hpp"
#include "Node.hpp"
#include "Line.hpp"
#include "Circle.hpp"
#include "Diamond.hpp"
#include "Reactangle.hpp"
#include "Style.hpp"
#include "Graph.hpp"
#include "DotCloud.hpp"
#pragma once

using namespace AST;
class Retranslator{
public:
    static Retranslator& getInstance(){
        if (!instance)
            instance = std::unique_ptr<Retranslator>(new Retranslator());
        return *instance;
    };

    ASTTree parseTree(std::map<std::string, Shape*> const& map);

private:
    Retranslator(){};
    Retranslator(const Retranslator&) = delete;
    Retranslator& operator=(const Retranslator&) = delete;
    
    static std::unique_ptr<Retranslator> instance;

    Node* makeObject(std::pair<std::string const, Shape*> const& pair) const;
    Node* makeNote(std::pair<std::string const, Shape*> const& pair) const;
    Node* makeLink(std::pair<std::string const, Shape*> const& pair) const;
    Node* makeGraph(std::pair<std::string const, Shape*> const& pair) const;
    Node* makeDotCloud(std::pair<std::string const, Shape*> const& pair) const;
};