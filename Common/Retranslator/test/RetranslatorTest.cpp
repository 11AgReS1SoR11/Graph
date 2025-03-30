#include <QtTest/QtTest>
#include <stdexcept>
#include <iostream>
#include "Retranslator.hpp"
using namespace AST;
class TestClass : public QObject
{
    Q_OBJECT

private slots:
    void test_objectDecl();
    void test_graph();
    void test_dotCloud();
};



void TestClass::test_objectDecl()
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

    Reactangle reactangle;
    reactangle.text = "reactangleTEXT";
    reactangle.id = "reactangleID";
    reactangle.x = 3;
    reactangle.y = 3;

    Shape* reactangle_ptr = &reactangle;
    vec.push_back(reactangle_ptr);

    Line line;
    line.text = "lineTEXT";
    line.id = "lineID";
    line.x = 4;
    line.y = 4;
    line.idFrom = "diamondID";
    line.idTo = "reactangleID";

    Shape* line_ptr = &line;
    vec.push_back(line_ptr);




    ASTTree tree(Retranslator::getInstance().parseTree(vec));
    auto it = tree.begin();
    QVERIFY(it->getValue() == "root");
    ++it;
    QVERIFY(it->getValue() == "@startgraph");
    ++it;

    ///circle-------------------------------

    QVERIFY(it->getValue() == "STATEMENT");
    ++it;
    QVERIFY(it->getValue() == "object_decl");
    ++it;
    QVERIFY(it->getValue() == "SHAPE");
    ++it;
    QVERIFY(it->getValue() == "circle");
    ++it;
    QVERIFY(it->getValue() == "ID");
    ++it;
    QVERIFY(it->getValue() == "circleID");
    ++it;
    QVERIFY(it->getValue() == "{");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "circleTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "radius");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");


    ++it;
    QVERIFY(it->getValue() == "}");
    ++it;

    ///circle end ----------------------------------

    /// diamond ------------------------------------
    
    QVERIFY(it->getValue() == "STATEMENT");
    ++it;
    QVERIFY(it->getValue() == "object_decl");
    ++it;
    QVERIFY(it->getValue() == "SHAPE");
    ++it;
    QVERIFY(it->getValue() == "diamond");
    ++it;
    QVERIFY(it->getValue() == "ID");
    ++it;
    QVERIFY(it->getValue() == "diamondID");
    ++it;
    QVERIFY(it->getValue() == "{");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "diamondTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "2");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "2");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_A");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_B");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "angle");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)90);
    ++it;
    QVERIFY(it->getValue() == ";");
    ++it;

    
    QVERIFY(it->getValue() == "}");
    ++it;

    ///diamond end ----------------------------

    ///reactangle -----------------------------
    
    QVERIFY(it->getValue() == "STATEMENT");
    ++it;
    QVERIFY(it->getValue() == "object_decl");
    ++it;
    QVERIFY(it->getValue() == "SHAPE");
    ++it;
    
    QVERIFY(it->getValue() == "reactangle");
    ++it;
    
    QVERIFY(it->getValue() == "ID");
    ++it;
    QVERIFY(it->getValue() == "reactangleID");
    ++it;
    QVERIFY(it->getValue() == "{");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    
    QVERIFY(it->getValue() == "reactangleTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "3");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "3");
    ++it;
    QVERIFY(it->getValue() == ";");
    
    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_A");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");


    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_B");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "}");


    ///reactangle end ---------------------------------

    ///line -----------------------------------------
    ++it;
    QVERIFY(it->getValue() == "STATEMENT");
    ++it;
    QVERIFY(it->getValue() == "relation");
    ++it;
    
    QVERIFY(it->getValue() == "ID");
    ++it;
    
    QVERIFY(it->getValue() == "diamondID");
    ++it;
    
    QVERIFY(it->getValue() == "ARROW");

    ++it;
    QVERIFY(it->getValue() == "-");
    ++it;

    QVERIFY(it->getValue() == "ID");
    ++it;
    QVERIFY(it->getValue() == "reactangleID");
    ++it;

    QVERIFY(it->getValue() == "{");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    
    QVERIFY(it->getValue() == "lineTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "4");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "4");
    ++it;
    QVERIFY(it->getValue() == ";");
    
    ++it;
    QVERIFY(it->getValue() == "}");

    ///line end------------------------------

    ++it;
    

    QVERIFY(it->getValue() == "@endgraph");
}


void TestClass::test_graph()
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

    Reactangle reactangle;
    reactangle.text = "reactangleTEXT";
    reactangle.id = "reactangleID";
    reactangle.x = 3;
    reactangle.y = 3;

    Shape* reactangle_ptr = &reactangle;

    Line line;
    line.text = "lineTEXT";
    line.id = "lineID";
    line.x = 4;
    line.y = 4;
    line.idFrom = "diamondID";
    line.idTo = "reactangleID";

    Shape* line_ptr = &line;

    Graph graph;
    graph.id = "graphID";
    graph.text = "graphTEXT";
    graph.x = 0;
    graph.y = 0;

    graph.nodes.push_back(circle_ptr);
    graph.nodes.push_back(diamond_ptr);
    graph.nodes.push_back(reactangle_ptr);
    graph.nodes.push_back(line_ptr);

    Shape* graph_ptr = &graph;
    
    vec.push_back(graph_ptr);
    
    ///start -------------------------------------
    ASTTree tree(Retranslator::getInstance().parseTree(vec));
    auto it = tree.begin();
    QVERIFY(it->getValue() == "root");
    ++it;
    QVERIFY(it->getValue() == "@startgraph");
    ++it;

    QVERIFY(it->getValue() == "STATEMENT");
    ++it;

    QVERIFY(it->getValue() == "graph");
    ++it;

    QVERIFY(it->getValue() == "ID");
    ++it;

    QVERIFY(it->getValue() == "graphID");
    ++it;

    QVERIFY(it->getValue() == "(");
    ++it;
    
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "graphTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "0");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "0");
    ++it;
    QVERIFY(it->getValue() == ";");
    ++it;
    

    QVERIFY(it->getValue() == ")");
    ++it;
    
    QVERIFY(it->getValue() == "{");


    ///circle-------------------------------------
    ++it;
    
    QVERIFY(it->getValue() == "object_decl");
    ++it;
    QVERIFY(it->getValue() == "SHAPE");
    ++it;
    QVERIFY(it->getValue() == "circle");
    ++it;
    QVERIFY(it->getValue() == "ID");
    ++it;
    QVERIFY(it->getValue() == "circleID");
    ++it;
    QVERIFY(it->getValue() == "{");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "circleTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");
    
    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "radius");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");


    ++it;
    QVERIFY(it->getValue() == "}");
    ++it;

    ///circle end ----------------------------------------



    ///diamond --------------------------------------------

    QVERIFY(it->getValue() == "object_decl");
    ++it;
    QVERIFY(it->getValue() == "SHAPE");
    ++it;
    QVERIFY(it->getValue() == "diamond");
    ++it;
    QVERIFY(it->getValue() == "ID");
    ++it;
    QVERIFY(it->getValue() == "diamondID");
    ++it;
    QVERIFY(it->getValue() == "{");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "diamondTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "2");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "2");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_A");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_B");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "angle");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)90);
    ++it;
    QVERIFY(it->getValue() == ";");
    ++it;

    
    QVERIFY(it->getValue() == "}");
    ++it;

    ///diamond end-------------------------------------------


    ///reactangle---------------------------------------

    QVERIFY(it->getValue() == "object_decl");
    ++it;
    QVERIFY(it->getValue() == "SHAPE");
    ++it;
    
    QVERIFY(it->getValue() == "reactangle");
    ++it;
    
    QVERIFY(it->getValue() == "ID");
    ++it;
    QVERIFY(it->getValue() == "reactangleID");
    ++it;
    QVERIFY(it->getValue() == "{");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    
    QVERIFY(it->getValue() == "reactangleTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "3");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "3");
    ++it;
    QVERIFY(it->getValue() == ";");
    
    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_A");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");


    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_B");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QCOMPARE(std::stod(it->getValue()), (double)1);
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "}");
    ++it;

    ///reactangle end-----------------------------------

    ///line------------------------------------------

    QVERIFY(it->getValue() == "relation");
    ++it;
    
    QVERIFY(it->getValue() == "ID");
    ++it;
    
    QVERIFY(it->getValue() == "diamondID");
    ++it;
    
    QVERIFY(it->getValue() == "ARROW");

    ++it;
    QVERIFY(it->getValue() == "-");
    ++it;

    QVERIFY(it->getValue() == "ID");
    ++it;
    QVERIFY(it->getValue() == "reactangleID");
    ++it;

    QVERIFY(it->getValue() == "{");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    
    QVERIFY(it->getValue() == "lineTEXT");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "сolor");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "TEXT");
    ++it;
    QVERIFY(it->getValue() == "NONE");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "border");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "1");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "size_text");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "10");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "x");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "4");
    ++it;
    QVERIFY(it->getValue() == ";");

    ++it;
    QVERIFY(it->getValue() == "property");
    ++it;
    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;
    QVERIFY(it->getValue() == "y");
    ++it;
    QVERIFY(it->getValue() == "=");
    ++it;
    QVERIFY(it->getValue() == "NUMBER");
    ++it;
    QVERIFY(it->getValue() == "4");
    ++it;
    QVERIFY(it->getValue() == ";");
    
    ++it;
    QVERIFY(it->getValue() == "}");
    ++it;

    ///line end-------------------------------------
    QVERIFY(it->getValue() == "}");
    ++it;
    QVERIFY(it->getValue() == "@endgraph");

}

void TestClass::test_dotCloud()
{
    std::vector<Shape*> vec;
    DotCloud cloud;

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
    QVERIFY(it->getValue() == "root");
    ++it;
    QVERIFY(it->getValue() == "@startgraph");
    ++it;

    QVERIFY(it->getValue() == "STATEMENT");
    ++it;

    
    
    QVERIFY(it->getValue() == "dot_cloud");
    ++it;

    QVERIFY(it->getValue() == "(");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;

    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;

    QVERIFY(it->getValue() == "grid");
    ++it;
    
    QVERIFY(it->getValue() == "=");
    ++it;

    QVERIFY(it->getValue() == "TEXT");
    ++it;
    

    QVERIFY(it->getValue() == "false");
    ++it;
    
    QVERIFY(it->getValue() == ")");
    ++it;

    ///first---------------------------------

    QVERIFY(it->getValue() == "{");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;

    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;

    QVERIFY(it->getValue() == "x");
    ++it;
    
    QVERIFY(it->getValue() == "=");
    ++it;

    QVERIFY(it->getValue() == "NUMBER");
    ++it;

    QVERIFY(it->getValue() == "1");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;

    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;

    QVERIFY(it->getValue() == "y");
    ++it;
    
    QVERIFY(it->getValue() == "=");
    ++it;

    QVERIFY(it->getValue() == "NUMBER");
    ++it;

    QVERIFY(it->getValue() == "1");
    ++it;

    QVERIFY(it->getValue() == "}");
    ++it;

    ///end of first------------------------------------------------

    ///second-------------------------------------------------

    QVERIFY(it->getValue() == "{");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;

    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;

    QVERIFY(it->getValue() == "x");
    ++it;
    
    QVERIFY(it->getValue() == "=");
    ++it;

    QVERIFY(it->getValue() == "NUMBER");
    ++it;

    QVERIFY(it->getValue() == "2");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;

    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;

    QVERIFY(it->getValue() == "y");
    ++it;
    
    QVERIFY(it->getValue() == "=");
    ++it;

    QVERIFY(it->getValue() == "NUMBER");
    ++it;

    QVERIFY(it->getValue() == "2");
    ++it;

    QVERIFY(it->getValue() == "}");
    ++it;

    ///end of second-------------------------------------------

    ///third---------------------------------------------------

    QVERIFY(it->getValue() == "{");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;

    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;

    QVERIFY(it->getValue() == "x");
    ++it;
    
    QVERIFY(it->getValue() == "=");
    ++it;

    QVERIFY(it->getValue() == "NUMBER");
    ++it;

    QVERIFY(it->getValue() == "3");
    ++it;

    QVERIFY(it->getValue() == "property");
    ++it;

    QVERIFY(it->getValue() == "PROPERTY_KEY");
    ++it;

    QVERIFY(it->getValue() == "y");
    ++it;
    
    QVERIFY(it->getValue() == "=");
    ++it;

    QVERIFY(it->getValue() == "NUMBER");
    ++it;

    QVERIFY(it->getValue() == "3");
    ++it;

    QVERIFY(it->getValue() == "}");
    ++it;

    ///end of third------------------------------------------

    QVERIFY(it->getValue() == "@endgraph");
}


QTEST_GUILESS_MAIN(TestClass)
#include "RetranslatorTest.moc"
