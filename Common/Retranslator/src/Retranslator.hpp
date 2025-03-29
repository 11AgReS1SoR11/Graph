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
#include "Note.hpp"
#pragma once

using namespace AST;
class Retranslator{
public:
    static Retranslator& getInstance(){
        if (!instance)
            instance = std::unique_ptr<Retranslator>(new Retranslator());
        return *instance;
    };

    ASTTree parseTree(std::vector<Shape*> const& vec) const;

private:
    Retranslator(){};
    Retranslator(const Retranslator&) = delete;
    Retranslator& operator=(const Retranslator&) = delete;
    
    static std::unique_ptr<Retranslator> instance;

    Node* makeObject(const Shape* const shape) const;
    Node* makeNote(const Note* const shape) const;
    Node* makeLink(const Line* const shape) const;
    Node* makeGraph(const Graph* const shape) const;
    Node* makeDotCloud(const DotCloud* const shape) const;
};