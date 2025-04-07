#include <catch2/catch_test_macros.hpp>

#include "Retranslator.hpp"

using namespace AST;

void checkCircle(AST::ASTTree::DSFIterator& it)
{
    
    REQUIRE(it->getValue() == "object_decl");
    ++it;
    REQUIRE(it->getValue() == "SHAPE");
    ++it;
    REQUIRE(it->getValue() == "circle");
    ++it;
    REQUIRE(it->getValue() == "ID");
    ++it;
    REQUIRE(it->getValue() == "circleID");
    ++it;
    REQUIRE(it->getValue() == "{");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "circleTEXT");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "color");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "none");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "border");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "1");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "10");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "x");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "1");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "y");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "1");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "radius");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(std::stod(it->getValue()) == 1);
    ++it;
    REQUIRE(it->getValue() == ";");


    ++it;
    REQUIRE(it->getValue() == "}");
    ++it;
}

void checkDiamond(AST::ASTTree::DSFIterator& it)
{
    REQUIRE(it->getValue() == "object_decl");
    ++it;
    REQUIRE(it->getValue() == "SHAPE");
    ++it;
    REQUIRE(it->getValue() == "diamond");
    ++it;
    REQUIRE(it->getValue() == "ID");
    ++it;
    REQUIRE(it->getValue() == "diamondID");
    ++it;
    REQUIRE(it->getValue() == "{");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "diamondTEXT");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "color");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "none");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "border");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "1");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "10");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "x");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "2");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "y");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "2");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_A");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(std::stod(it->getValue()) == 1);
    ++it;
    REQUIRE(it->getValue() == ";");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_B");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(std::stod(it->getValue()) == 1);
    ++it;
    REQUIRE(it->getValue() == ";");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "angle");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(std::stod(it->getValue()) == 90);
    ++it;
    REQUIRE(it->getValue() == ";");
    ++it;

    
    REQUIRE(it->getValue() == "}");
    ++it;

}

void checkReactangle(AST::ASTTree::DSFIterator& it)
{
    REQUIRE(it->getValue() == "object_decl");
    ++it;
    REQUIRE(it->getValue() == "SHAPE");
    ++it;
    
    REQUIRE(it->getValue() == "rectangle");
    ++it;
    
    REQUIRE(it->getValue() == "ID");
    ++it;
    REQUIRE(it->getValue() == "rectangleID");
    ++it;
    REQUIRE(it->getValue() == "{");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    
    REQUIRE(it->getValue() == "rectangleTEXT");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "color");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "none");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "border");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "1");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "10");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "x");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "3");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "y");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "3");
    ++it;
    REQUIRE(it->getValue() == ";");
    
    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_A");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(std::stod(it->getValue()) == 1);
    ++it;
    REQUIRE(it->getValue() == ";");


    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_B");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(std::stod(it->getValue()) == 1);
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "}");
    ++it;

}

void checkLine(AST::ASTTree::DSFIterator& it)
{
    REQUIRE(it->getValue() == "relation");
    ++it;
    
    REQUIRE(it->getValue() == "ID");
    ++it;
    
    REQUIRE(it->getValue() == "diamondID");
    ++it;
    
    REQUIRE(it->getValue() == "ARROW");

    ++it;
    REQUIRE(it->getValue() == "-");
    ++it;

    REQUIRE(it->getValue() == "ID");
    ++it;
    REQUIRE(it->getValue() == "rectangleID");
    ++it;

    REQUIRE(it->getValue() == "{");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    
    REQUIRE(it->getValue() == "lineTEXT");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "color");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "none");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "border");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "1");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "10");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "x");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "4");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "y");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "4");
    ++it;
    REQUIRE(it->getValue() == ";");
    
    ++it;
    REQUIRE(it->getValue() == "}");

    ++it;

}

void checkNote(AST::ASTTree::DSFIterator& it)
{
    REQUIRE(it->getValue() == "NOTE");
    ++it;

    REQUIRE(it->getValue() == "note");
    ++it;
    
    REQUIRE(it->getValue() == "ID");
    ++it;
    
    REQUIRE(it->getValue() == "noteID");
    ++it;
    
    REQUIRE(it->getValue() == "{");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    
    REQUIRE(it->getValue() == "crocodilo bombordiro");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "color");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "none");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "border");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "1");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "10");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "x");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "5");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "y");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "5");
    ++it;
    REQUIRE(it->getValue() == ";");
    
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_A");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(std::stod(it->getValue()) == 1);
    ++it;
    REQUIRE(it->getValue() == ";");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_B");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(std::stod(it->getValue()) == 1);
    ++it;
    REQUIRE(it->getValue() == ";");
    ++it;
    


    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "idTo");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "lineID");
    ++it;
    REQUIRE(it->getValue() == ";");
    ++it;

    REQUIRE(it->getValue() == "}");

    ++it;

}



TEST_CASE("Check objects retranslate", "[Retranslator]")
{
    std::vector<Shape*> vec;

    Circle circle;
    circle.text = "circleTEXT";
    circle.id = "circleID";
    circle.x = 1;
    circle.y = 1;

    Shape* circle_ptr = &circle;
    vec.push_back(circle_ptr);

    Diamond diamond;
    diamond.text = "diamondTEXT";
    diamond.id = "diamondID";
    diamond.x = 2;
    diamond.y = 2;

    Shape* diamond_ptr = &diamond;
    vec.push_back(diamond_ptr);

    Rectangle rectangle;
    rectangle.text = "rectangleTEXT";
    rectangle.id = "rectangleID";
    rectangle.x = 3;
    rectangle.y = 3;

    Shape* rectangle_ptr = &rectangle;
    vec.push_back(rectangle_ptr);

    Line line;
    line.text = "lineTEXT";
    line.id = "lineID";
    line.x = 4;
    line.y = 4;
    line.idFrom = "diamondID";
    line.idTo = "rectangleID";

    Shape* line_ptr = &line;
    vec.push_back(line_ptr);

    Note note;
    note.text = "crocodilo bombordiro";
    note.id = "noteID";
    note.x = 5;
    note.y = 5;
    note.idTo = "lineID";

    vec.push_back(&note);



    ASTTree tree(Retranslator::getInstance().parseTree(vec));
    auto it = tree.begin();
    REQUIRE(it->getValue() == "root");
    ++it;
    REQUIRE(it->getValue() == "@startgraph");
    ++it;

    REQUIRE(it->getValue() == "statement");
    ++it;

    checkCircle(it);
    
    REQUIRE(it->getValue() == "statement");
    ++it;

    checkDiamond(it);
    
    REQUIRE(it->getValue() == "statement");
    ++it;

    checkReactangle(it);

    REQUIRE(it->getValue() == "statement");
    ++it;

    checkLine(it);    

    REQUIRE(it->getValue() == "statement");
    ++it;

    checkNote(it);

    REQUIRE(it->getValue() == "@endgraph");
}

TEST_CASE("Check graph retranslate", "[Retranslator]")
{
    std::vector<Shape*> vec;

    Circle circle;
    circle.text = "circleTEXT";
    circle.id = "circleID";
    circle.x = 1;
    circle.y = 1;

    Shape* circle_ptr = &circle;

    Diamond diamond;
    diamond.text = "diamondTEXT";
    diamond.id = "diamondID";
    diamond.x = 2;
    diamond.y = 2;

    Shape* diamond_ptr = &diamond;

    Rectangle rectangle;
    rectangle.text = "rectangleTEXT";
    rectangle.id = "rectangleID";
    rectangle.x = 3;
    rectangle.y = 3;

    Shape* rectangle_ptr = &rectangle;

    Line line;
    line.text = "lineTEXT";
    line.id = "lineID";
    line.x = 4;
    line.y = 4;
    line.idFrom = "diamondID";
    line.idTo = "rectangleID";

    Shape* line_ptr = &line;

    Graph graph;
    graph.id = "graphID";
    graph.text = "graphTEXT";
    graph.x = 0;
    graph.y = 0;

    graph.nodes.push_back(circle_ptr);
    graph.nodes.push_back(diamond_ptr);
    graph.nodes.push_back(rectangle_ptr);
    graph.nodes.push_back(line_ptr);

    Shape* graph_ptr = &graph;
    
    vec.push_back(graph_ptr);
    
    ///start -------------------------------------
    ASTTree tree(Retranslator::getInstance().parseTree(vec));
    auto it = tree.begin();
    REQUIRE(it->getValue() == "root");
    ++it;
    REQUIRE(it->getValue() == "@startgraph");
    ++it;

    REQUIRE(it->getValue() == "statement");
    ++it;

    REQUIRE(it->getValue() == "GRAPH");
    ++it;

    REQUIRE(it->getValue() == "graph");
    ++it;

    REQUIRE(it->getValue() == "ID");
    ++it;

    REQUIRE(it->getValue() == "graphID");
    ++it;

    REQUIRE(it->getValue() == "(");
    ++it;
    
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "graphTEXT");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "color");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "TEXT");
    ++it;
    REQUIRE(it->getValue() == "none");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "border");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "1");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "size_text");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "10");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "x");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "0");
    ++it;
    REQUIRE(it->getValue() == ";");

    ++it;
    REQUIRE(it->getValue() == "property");
    ++it;
    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;
    REQUIRE(it->getValue() == "y");
    ++it;
    REQUIRE(it->getValue() == "=");
    ++it;
    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    REQUIRE(it->getValue() == "0");
    ++it;
    REQUIRE(it->getValue() == ";");
    ++it;
    

    REQUIRE(it->getValue() == ")");
    ++it;
    
    REQUIRE(it->getValue() == "{");
    ++it;
    
    checkCircle(it);

    checkDiamond(it);

    checkReactangle(it);

    checkLine(it);

    REQUIRE(it->getValue() == "}");
    ++it;
    REQUIRE(it->getValue() == "@endgraph");

}

TEST_CASE("Check dot_cloud retranslate", "[Retranslator]")
{
    std::vector<Shape*> vec;
    DotCloud cloud;

    cloud.x = 0;
    cloud.y = 0;

    Circle circle1;
    circle1.x = 1;
    circle1.y = 1;

    Circle* circle1_ptr = &circle1;

    Circle circle2;
    circle2.x = 2;
    circle2.y = 2;

    Circle* circle2_ptr = &circle2;

    Circle circle3;
    circle3.x = 3;
    circle3.y = 3;

    Circle* circle3_ptr = &circle3;

    cloud.dots.push_back(circle1_ptr);
    cloud.dots.push_back(circle2_ptr);
    cloud.dots.push_back(circle3_ptr);

    vec.push_back(&cloud);

    ASTTree tree(Retranslator::getInstance().parseTree(vec));
    auto it = tree.begin();
    REQUIRE(it->getValue() == "root");
    ++it;
    REQUIRE(it->getValue() == "@startgraph");
    ++it;

    REQUIRE(it->getValue() == "statement");
    ++it;
    
    REQUIRE(it->getValue() == "DOT_CLOUD");
    ++it;

    REQUIRE(it->getValue() == "dot_cloud");
    ++it;

    REQUIRE(it->getValue() == "(");
    ++it;

    ///params ---------------------------------

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "text");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "TEXT");
    ++it;
    

    REQUIRE(it->getValue() == "");
    ++it;
    
    REQUIRE(it->getValue() == ";");
    ++it;
    
    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    

    REQUIRE(it->getValue() == "color");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "TEXT");
    ++it;
    

    REQUIRE(it->getValue() == "none");
    ++it;

    REQUIRE(it->getValue() == ";");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "border");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    

    REQUIRE(it->getValue() == "1");
    ++it;


    REQUIRE(it->getValue() == ";");
    ++it;


    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "size_text");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    

    REQUIRE(it->getValue() == "10");
    ++it;

    REQUIRE(it->getValue() == ";");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "x");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    

    REQUIRE(it->getValue() == "0");
    ++it;

    REQUIRE(it->getValue() == ";");
    ++it;


    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "y");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;
    

    REQUIRE(it->getValue() == "0");
    ++it;

    REQUIRE(it->getValue() == ";");
    ++it;
    
    ///params end --------------------------------




    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "grid");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "TEXT");
    ++it;
    

    REQUIRE(it->getValue() == "false");
    ++it;
    
    REQUIRE(it->getValue() == ";");
    ++it;

    REQUIRE(it->getValue() == ")");
    ++it;

   
    ///first---------------------------------

    REQUIRE(it->getValue() == "{");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "x");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;

    REQUIRE(it->getValue() == "1");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "y");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;

    REQUIRE(it->getValue() == "1");
    ++it;

    REQUIRE(it->getValue() == "}");
    ++it;

    ///end of first------------------------------------------------

    ///second-------------------------------------------------

    REQUIRE(it->getValue() == "{");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "x");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;

    REQUIRE(it->getValue() == "2");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "y");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;

    REQUIRE(it->getValue() == "2");
    ++it;

    REQUIRE(it->getValue() == "}");
    ++it;

    ///end of second-------------------------------------------

    ///third---------------------------------------------------

    REQUIRE(it->getValue() == "{");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "x");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;

    REQUIRE(it->getValue() == "3");
    ++it;

    REQUIRE(it->getValue() == "property");
    ++it;

    REQUIRE(it->getValue() == "PROPERTY_KEY");
    ++it;

    REQUIRE(it->getValue() == "y");
    ++it;
    
    REQUIRE(it->getValue() == "=");
    ++it;

    REQUIRE(it->getValue() == "NUMBER");
    ++it;

    REQUIRE(it->getValue() == "3");
    ++it;

    REQUIRE(it->getValue() == "}");
    ++it;

    ///end of third------------------------------------------

    REQUIRE(it->getValue() == "@endgraph");
}
