#include <Retranslator.hpp>
#include <typeinfo>

Retranslator& Retranslator::getInstance(){
    if (!instance)
        instance = std::unique_ptr<Retranslator>(new Retranslator());
    return *instance;
}


ASTTree* Retranslator::parseTree(std::unordered_map<std::string, Shape*> map){
    
    Node* root = new Node("root");
    root->addChild(new Node("STARTGRAPH"));

    for (const auto& elem : map)
    {
        start->addChild(new Node("STATEMENT"));
        if (dynamic_cast<Note*>(elem.second))
        {
            start->addChild(makeNote(elem.second));
        }
        else if (dynamic_cast<Line*>(elem.second))
        {
            start->addChild(makeLink(elem.second));
        }
        else 
        {
            start->addChild(makeObject(elem.second));
        }
    }

    start->addChild(new Node("ENDGRAPH"));
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
    node->addChild(doubleNode(value, value, isText));
    node->addChild(new Node(";"));
}

Node* makeObject(Shape* shape) const
{
    Node* node = new Node("object_decl");
    node->addChild(new Node("SHAPE"));

    if (dynamic_cast<Circle*>(shape))
        node->childNodes[0]->addChild(new Node("circle"));
    else if (dynamic_cast<Diamond*>(shape))
        node->childNodes[0]->addChild(new Node("diamond"));
    else if (dynamic_cast<Rectangle*>(shape))
        node->childNodes[0]->addChild(new Node("rectangle"));

    node->addChild(new Node("ID"));
    node->childNodes[1]->addChild(new Node(""));

    node->addChild(new Node("{"));

    //общая часть
    
    addProperty(node, "text", shape->text, true);
    addProperty(node, "сolor", std::to_string(static_cast<short>(shape->style->color)));
    addProperty(node, "border", std::to_string(shape->style->border));
    addProperty(node, "size_text", std::to_string(shape->style->textSize));
    addProperty(node, "x", std::to_string(shape->style->x));
    addProperty(node, "y", std::to_string(shape->style->y));

    if (dynamic_cast<Circle*>(shape))
    {   
        Circle* circle = static_cast<Circle*>(shape);
        addProperty(node, "radius", std::to_string(circle->radius));
    }

    else if (dynamic_cast<Diamond*>(shape))
    {
        Diamond* diamond = static_cast<Diamond*>(shape);
        addProperty(node, "size_A", std::to_string(Diamond->sizeA));
        addProperty(node, "size_B", std::to_string(Diamond->sizeB));
        addProperty(node, "angle", std::to_string(Diamond->angle));
    }

    else if (dynamic_cast<Rectangle*>(shape))
    {
        Reactangle* reactangle = static_cast<Reactangle*>(shape);
        addProperty(node, "size_A", std::to_string(reactangle->sizeA));
        addProperty(node, "size_B", std::to_string(reactangle->sizeB));
    }

    node->addChild(new Node("}"));

    return node;

}

Node* makeNote(Shape* shape) const
{
    //to be inmpelented...
}

Node* makeLink(Shape* shape) const
{
    Node* node = new Node("relation");
    
    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape->idFrom));

    node->addChild(new Node("ARROW"));
    node->childNodes[1]->addChild(new Node(std::to_string(static_cast<short>(shape->orientation))));

    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape->idTo));

    node->addChild(new Node("{"));

    addProperty(node, type, std::to_string(static_cast<short>(shape->orientation)));

    node->addChild(new Node("{"));
}