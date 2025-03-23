#include "Retranslator.hpp"
#include <typeinfo>

using namespace AST;

std::unique_ptr<Retranslator> Retranslator::instance = nullptr;

ASTTree Retranslator::parseTree(std::unordered_map<std::string, Shape*> map){
    
    Node* root = new Node("root");
    root->addChild(new Node("STARTGRAPH"));

    for (const auto& elem : map)
    {
        root->addChild(new Node("STATEMENT"));
        // if (dynamic_cast<Note*>(elem.second))
        // {
        //     root->addChild(makeNote(elem));
        // }
        if (dynamic_cast<Line*>(elem.second))
        {
            root->addChild(makeLink(elem));
        }
        else 
        {
            root->addChild(makeObject(elem));
        }
    }

    root->addChild(new Node("ENDGRAPH"));

    return ASTTree(root);
}

Node* doubleNode(std::string key, std::string value, bool isText){
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

void addProperty(Node* node, std::string key, std::string value, bool isText = false)
{
    node->addChild(doubleNode(key, value, isText));
    node->addChild(new Node(";"));
}

Node* Retranslator::makeObject(std::pair<std::string, Shape*> pair) const
{
    Shape* shape = pair.second;
    Node* node = new Node("object_decl");
    node->addChild(new Node("SHAPE"));

    if (dynamic_cast<Circle*>(shape))
        node->childNodes[0]->addChild(new Node("circle"));
    else if (dynamic_cast<Diamond*>(shape))
        node->childNodes[0]->addChild(new Node("diamond"));
    else if (dynamic_cast<Reactangle*>(shape))
        node->childNodes[0]->addChild(new Node("rectangle"));

    node->addChild(new Node("ID"));
    node->childNodes[1]->addChild(new Node(pair.first));

    node->addChild(new Node("{"));

    //общая часть
    
    addProperty(node, "text", shape->text, true);
    addProperty(node, "сolor", std::to_string(static_cast<short>(shape->style.color)));
    addProperty(node, "border", std::to_string(shape->style.border));
    addProperty(node, "size_text", std::to_string(shape->style.textSize));
    addProperty(node, "x", std::to_string(shape->x));
    addProperty(node, "y", std::to_string(shape->y));

    if (dynamic_cast<Circle*>(shape))
    {   
        Circle* circle = static_cast<Circle*>(shape);
        addProperty(node, "radius", std::to_string(circle->radius));
    }

    else if (dynamic_cast<Diamond*>(shape))
    {
        Diamond* diamond = static_cast<Diamond*>(shape);
        addProperty(node, "size_A", std::to_string(diamond->sizeA));
        addProperty(node, "size_B", std::to_string(diamond->sizeB));
        addProperty(node, "angle", std::to_string(diamond->angle));
    }

    else if (dynamic_cast<Reactangle*>(shape))
    {
        Reactangle* reactangle = static_cast<Reactangle*>(shape);
        addProperty(node, "size_A", std::to_string(reactangle->sizeA));
        addProperty(node, "size_B", std::to_string(reactangle->sizeB));
    }

    node->addChild(new Node("}"));

    return node;

}

// Node* Retranslator::makeNote(std::pair<std::string, Shape*> pair) const
// {
//     //to be inmpelented...
// }

Node* Retranslator::makeLink(std::pair<std::string, Shape*> pair) const
{
    Line* shape = static_cast<Line*>(pair.second);
    Node* node = new Node("relation");
    
    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(pair.first));

    node->addChild(new Node("ARROW"));
    node->childNodes[1]->addChild(new Node(std::to_string(static_cast<short>(shape->orientation))));

    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape->idTo));

    node->addChild(new Node("{"));

    addProperty(node, "type", std::to_string(static_cast<short>(shape->orientation)));

    node->addChild(new Node("{"));
}