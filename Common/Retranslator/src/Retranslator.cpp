#include "Retranslator.hpp"
#include <typeinfo>
#include "Logger.hpp"

using namespace AST;

std::unique_ptr<Retranslator> Retranslator::instance = nullptr;

bool isObject(const Shape* shape)
{
    if (dynamic_cast<const Circle*>(shape))
        return true;
    if (dynamic_cast<const Diamond*>(shape))
        return true;
    if (dynamic_cast<const Rectangle*>(shape))
        return true;

    return false;

}

ASTTree Retranslator::parseTree(std::vector<Shape*> const& vec) const{
    
    Node* root = new Node("root");
    root->addChild(new Node("@startgraph"));

    for (const auto& elem : vec)
    {
        Node* cur = new Node("statement");
        root->addChild(cur);
        if (const Note* const note = dynamic_cast<const Note* const>(elem))
        {
            root->addChild(makeNote(*note));
        }
        else if (const Line* const line = dynamic_cast<const Line* const>(elem))
        {
            cur->addChild(makeLink(*line));
        }
        else if (const Graph* const graph = dynamic_cast<const Graph* const>(elem))
        {
            cur->addChild(makeGraph(*graph));
        }
        else if (const DotCloud* const cloud = dynamic_cast<const DotCloud* const>(elem))
        {
            cur->addChild(makeDotCloud(*cloud));
        }
        else if (isObject(elem))
        {
            cur->addChild(makeObject(*elem));
        }
        else 
        {
            std::string errMsg("wrong figure in parseTree function");
            LOG_ERROR(RETRANSLATOR_LOG, errMsg);
            throw std::invalid_argument(errMsg);
        }
    }

    root->addChild(new Node("@endgraph"));

    return ASTTree(root);
}

Node* makeNodeWithProperty(std::string const& key, std::string const& value, bool isText){
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

void addBasicParams(Node* node, const Shape& shape)
{
    addProperty(node, "text", shape.text, true);
    addProperty(node, "color", style_helper::colorToString(shape.style.color), true);
    addProperty(node, "border", std::to_string(shape.style.border));
    addProperty(node, "size_text", std::to_string(shape.style.textSize));
    addProperty(node, "x", std::to_string(shape.x));
    addProperty(node, "y", std::to_string(shape.y));
}

Node* Retranslator::makeObject(const Shape& shape) const
{
    Node* node = new Node("object_decl");
    node->addChild(new Node("SHAPE"));

    if (dynamic_cast<const Circle*>(&shape))
        node->childNodes[0]->addChild(new Node("circle"));
    else if (dynamic_cast<const Diamond*>(&shape))
        node->childNodes[0]->addChild(new Node("diamond"));
    else if (dynamic_cast<const Rectangle*>(&shape))
        node->childNodes[0]->addChild(new Node("rectangle"));

    node->addChild(new Node("ID"));
    node->childNodes[1]->addChild(new Node(shape.id));

    node->addChild(new Node("{"));

    addBasicParams(node, shape);

    if (const Circle* circle = dynamic_cast<const Circle*>(&shape))
    {   
        addProperty(node, "radius", std::to_string(circle->radius));
    }

    else if (const Diamond* diamond = dynamic_cast<const Diamond*>(&shape))
    {
        addProperty(node, "size_A", std::to_string(diamond->sizeA));
        addProperty(node, "size_B", std::to_string(diamond->sizeB));
        addProperty(node, "angle", std::to_string(diamond->angle));
    }

    else if (const Rectangle* rectangle = dynamic_cast<const Rectangle*>(&shape))
    {
        addProperty(node, "size_A", std::to_string(rectangle->sizeA));
        addProperty(node, "size_B", std::to_string(rectangle->sizeB));
    }

    node->addChild(new Node("}"));

    return node;

}

std::string arrowMaker(const Line& line)
{
    if (static_cast<short>(line.type) == 0 && static_cast<short>(line.orientation) == 0)
        return "--";
    else if (static_cast<short>(line.type) == 0 && static_cast<short>(line.orientation) == 1)
        return "-->";    
    else if (static_cast<short>(line.type) == 0 && static_cast<short>(line.orientation) == 2)
        return "<-->"; 
    else if (static_cast<short>(line.type) == 1 && static_cast<short>(line.orientation) == 0)
        return "-";
    else if (static_cast<short>(line.type) == 1 && static_cast<short>(line.orientation) == 1)
        return "->";    
    else 
        return "<->";   
}

Node* Retranslator::makeLink(const Line& shape) const
{
    Node* node = new Node("relation");
    
    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape.idFrom));

    node->addChild(new Node("ARROW"));
    node->childNodes[1]->addChild(new Node(arrowMaker(shape)));

    node->addChild(new Node("ID"));
    node->childNodes[2]->addChild(new Node(shape.idTo));

    node->addChild(new Node("{"));

    addBasicParams(node, shape);

    node->addChild(new Node("}"));

    return node;
}



Node* Retranslator::makeGraph(const Graph& shape) const
{
    Node* node = new Node("graph");

    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape.id));
    
    node->addChild(new Node("("));

    addBasicParams(node, shape);

    node->addChild(new Node(")"));

    node->addChild(new Node("{"));

    for (auto const& elem : shape.nodes)
    {
        if (const Line* line = dynamic_cast<const Line*>(elem))
        { 
            node->addChild(makeLink(*line));
        }
        else if (isObject(elem))
        {
            node->addChild(makeObject(*elem));
        }
        else 
        {
            std::string errMsg("wrong figure in parseTree function");
            LOG_ERROR(RETRANSLATOR_LOG, errMsg);
            throw std::invalid_argument(errMsg);
        }
    }

    node->addChild(new Node("}"));
    
    return node;

}


Node* Retranslator::makeDotCloud(const DotCloud& shape) const
{
    Node* node = new Node("dot_cloud");

    node->addChild(new Node("("));
    addBasicParams(node, shape);
    addProperty(node, "grid", shape.grid ? "true" : "false", true);
    node->addChild(new Node (")"));

    

    for (auto const& elem : shape.dots)
    {
        node->addChild(new Node("{"));
        node->addChild(makeNodeWithProperty("x", std::to_string(elem->x), false));
        node->addChild(makeNodeWithProperty("y", std::to_string(elem->y), false));
        node->addChild(new Node("}"));
    }


    

    return node;
}

Node* Retranslator::makeNote(const Note& shape) const
{
    Node* node = new Node("note");

    node->addChild(new Node("ID"));
    node->childNodes[0]->addChild(new Node(shape.id));

    node->addChild(new Node("{"));
    addBasicParams(node, shape);
    addProperty(node, "size_A", std::to_string(shape.sizeA));
    addProperty(node, "size_B", std::to_string(shape.sizeB));
    addProperty(node, "idTo", shape.idTo, true);
    node->addChild(new Node("}"));

    return node;

}