#include "Retranslator.hpp"
#include <typeinfo>
#include <iostream>
using namespace AST;

std::unique_ptr<Retranslator> Retranslator::instance = nullptr;

ASTTree Retranslator::parseTree(std::vector<Shape*> const& vec){
    
    Node* root = new Node("root");
    root->addChild(new Node("STARTGRAPH"));

    for (const auto& elem : vec)
    {
        Node* cur = new Node("STATEMENT");
        root->addChild(cur);
        // if (dynamic_cast<Note*>(elem.second))
        // {
        //     root->addChild(makeNote(elem));
        // }
        if (const Line* const line = dynamic_cast<const Line* const>(elem))
        {
            cur->addChild(makeLink(line));
        }
        else 
        {
            cur->addChild(makeObject(elem));
        }
    }

    root->addChild(new Node("ENDGRAPH"));

    return ASTTree(root);
}

Node* makeNodeWithProperty(std::string key, std::string value, bool isText){
    Node* property = new Node("property");
    property->addChild(new Node("PROPERTY_KEY"));
    property->childNodes[0]->addChild(new Node(key));
    property->addChild(new Node("="));
    if (isText)
        property->addChild(new Node("TEXT"));
    else 
        property->addChild(new Node("NUMBER"));
    property->childNodes[2]->addChild(new Node(value));

    return property;
}

void addProperty(Node* node, std::string const& key, std::string const& value, bool isText = false)
{
    node->addChild(makeNodeWithProperty(key, value, isText));
    node->addChild(new Node(";"));
}

void addBasicParams(Node* node, const Shape* const shape)
{
    addProperty(node, "text", shape->text, true);
    addProperty(node, "сolor", std::to_string(static_cast<short>(shape->style.color)));
    addProperty(node, "border", std::to_string(shape->style.border));
    addProperty(node, "size_text", std::to_string(shape->style.textSize));
    addProperty(node, "x", std::to_string(shape->x));
    addProperty(node, "y", std::to_string(shape->y));
}

Node* Retranslator::makeObject(const Shape* const shape) const
{
    Node* node = new Node("object_decl");
    node->addChild(new Node("SHAPE"));

    if (dynamic_cast<const Circle* const>(shape))
        node->childNodes[0]->addChild(new Node("circle"));
    else if (dynamic_cast<const Diamond* const>(shape))
        node->childNodes[0]->addChild(new Node("diamond"));
    else if (dynamic_cast<const Reactangle* const>(shape))
        node->childNodes[0]->addChild(new Node("reactangle"));

    node->addChild(new Node("ID"));
    node->childNodes[1]->addChild(new Node(shape->id));

    node->addChild(new Node("{"));

    addBasicParams(node, shape);

    if (const Circle* const circle = dynamic_cast<const Circle* const>(shape))
    {   
        addProperty(node, "radius", std::to_string(circle->radius));
    }

    else if (const Diamond* const diamond = dynamic_cast<const Diamond* const>(shape))
    {
        addProperty(node, "size_A", std::to_string(diamond->sizeA));
        addProperty(node, "size_B", std::to_string(diamond->sizeB));
        addProperty(node, "angle", std::to_string(diamond->angle));
    }

    else if (const Reactangle* const reactangle = dynamic_cast<const Reactangle* const>(shape))
    {
        addProperty(node, "size_A", std::to_string(reactangle->sizeA));
        addProperty(node, "size_B", std::to_string(reactangle->sizeB));
    }

    node->addChild(new Node("}"));

    return node;

}

// Node* Retranslator::makeNote(const Shape* const shape) const
// {
//     //to be inmpelented...
// }

std::string arrowMaker(const Line* const line)
{
    if (static_cast<short>(line->type) == 0 && static_cast<short>(line->orientation) == 0)
        return "--";
    else if (static_cast<short>(line->type) == 0 && static_cast<short>(line->orientation) == 1)
        return "-->";    
    else if (static_cast<short>(line->type) == 0 && static_cast<short>(line->orientation) == 2)
        return "<-->"; 
    else if (static_cast<short>(line->type) == 1 && static_cast<short>(line->orientation) == 0)
        return "-";
    else if (static_cast<short>(line->type) == 1 && static_cast<short>(line->orientation) == 1)
        return "->";    
    else 
        return "<->";   
}

Node* Retranslator::makeLink(const Line* const shape) const
{
    Node* node = new Node("relation");
    
    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape->idFrom));

    node->addChild(new Node("ARROW"));
    node->childNodes[1]->addChild(new Node(arrowMaker(shape)));

    node->addChild(new Node("ID"));
    node->childNodes[2]->addChild(new Node(shape->idTo));

    node->addChild(new Node("{"));

    addBasicParams(node, shape);

    node->addChild(new Node("}"));

    return node;
}

Node* Retranslator::makeGraph(const Graph* const shape) const
{
    Node* node = new Node("graph");

    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape->id));

    addBasicParams(node, shape);

    node->addChild(new Node("{"));

    for (auto const& elem : shape->nodes)
    {
        if (const Line* const line = dynamic_cast<const Line* const>(elem))
        { 
            node->addChild(makeLink(line));
        }
        else 
        {
            node->addChild(makeObject(elem));
        }
    }

    node->addChild(new Node("}"));

    return node;

}


Node* Retranslator::makeDotCloud(const DotCloud* const shape) const
{
    Node* node = new Node("dot_cloud");

    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape->id));

    addBasicParams(node, shape);

    node->addChild(new Node("{"));

    for (auto const& elem : shape->dots)
    {
        node->addChild(makeObject(elem));
    }

    node->addChild(new Node("}"));

    return node;
}
