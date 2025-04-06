#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "Translator.hpp"

TEST_CASE("Translate objects", "[Translator]"){
    std::vector<std::pair<std::string, std::any>> parsed_ast_tree;

    SEMANTICANALYZER::ObjectDecl circle, rectangle, diamond;

    std::vector<SEMANTICANALYZER::Property> circle_property, rectangle_property, diamond_property;

    // circle property
    circle.id = "crcl";
    circle.shape = "circle";
    circle_property.push_back({"text", "here is circle"});
    circle_property.push_back({"x", "4"}); 
    circle_property.push_back({"y", "3"}); 
    circle_property.push_back({"color", "RED"});
    circle_property.push_back({"border", "2"});
    circle_property.push_back({"size_text", "10"});
    circle_property.push_back({"radius", "5"});
    circle.properties = circle_property;

    // rectangle property
    rectangle.id = "rctngl";
    rectangle.shape = "rectangle";
    rectangle_property.push_back({"text", "here is rectangle"});
    rectangle_property.push_back({"x", "8"});
    rectangle_property.push_back({"y", "9"});
    rectangle_property.push_back({"color", "BLUE"});
    rectangle_property.push_back({"border", "2"});
    rectangle_property.push_back({"size_text", "10"});
    rectangle_property.push_back({"size_A", "3"});
    rectangle_property.push_back({"size_B", "4"});
    rectangle.properties = rectangle_property;

    // diamond property
    diamond.id = "dmnd";
    diamond.shape = "diamond";
    diamond_property.push_back({"text", "here is diamond"});
    diamond_property.push_back({"x", "8"});
    diamond_property.push_back({"y", "9"});
    diamond_property.push_back({"color", "NONE"});
    diamond_property.push_back({"border", "2"});
    diamond_property.push_back({"size_text", "10"});
    diamond_property.push_back({"size_A", "6"});
    diamond_property.push_back({"size_B", "4"});
    diamond_property.push_back({"angle","75"});
    diamond.properties = diamond_property;


    parsed_ast_tree.push_back({"object_decl", circle});
    parsed_ast_tree.push_back({"object_decl", rectangle});
    parsed_ast_tree.push_back({"object_decl", diamond});

    Translator tr;
    FiguresStorage result_tree = tr.translate(parsed_ast_tree);

    // check Circle
    Shape* shape = result_tree[0];
    REQUIRE(shape);
    REQUIRE(shape->id == "crcl");
    REQUIRE(shape->text == "here is circle");
    REQUIRE(style_helper::colorToString(shape->style.color) == "RED");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 4);
    REQUIRE(shape->y == 3);

    Circle* circleAfterTranslate = dynamic_cast<Circle*>(result_tree[0]);
    REQUIRE(circleAfterTranslate);
    REQUIRE(circleAfterTranslate->radius == 5);

    // check rectangle
    shape = result_tree[1];
    REQUIRE(shape);
    REQUIRE(shape->id == "rctngl");
    REQUIRE(shape->text == "here is rectangle");
    REQUIRE(style_helper::colorToString(shape->style.color) == "BLUE");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 8);
    REQUIRE(shape->y == 9);

    Rectangle* rectangleAfterTranslate = dynamic_cast<Rectangle*>(result_tree[1]);
    REQUIRE(rectangleAfterTranslate);
    REQUIRE(rectangleAfterTranslate->sizeA == 3);
    REQUIRE(rectangleAfterTranslate->sizeB == 4);

    //check diamond
    shape = result_tree[2];
    REQUIRE(shape);
    REQUIRE(shape->id == "dmnd");
    REQUIRE(shape->text == "here is diamond");
    REQUIRE(style_helper::colorToString(shape->style.color) == "NONE");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 8);
    REQUIRE(shape->y == 9);

    Diamond* diamondAfterTranslate = dynamic_cast<Diamond*>(result_tree[2]);
    REQUIRE(diamondAfterTranslate);
    REQUIRE(diamondAfterTranslate->sizeA == 6);
    REQUIRE(diamondAfterTranslate->sizeB == 4);
    REQUIRE(diamondAfterTranslate->angle == 75);
}

TEST_CASE("Translate relations", "[Translator]"){
    std::vector<std::pair<std::string, std::any>> parsed_ast_tree;

    SEMANTICANALYZER::Relation line1, line2, line3;

    std::vector<SEMANTICANALYZER::Property> line1_property, line2_property, line3_property;

    //fill line1
    line1.id1 = "crcl";
    line1.id2 = "rctngl";
    line1.arrow = "<-->";
    line1_property.push_back({"text", "here is line1"});
    line1_property.push_back({"x", "4"}); 
    line1_property.push_back({"y", "3"}); 
    line1_property.push_back({"color", "RED"});
    line1_property.push_back({"border", "2"});
    line1_property.push_back({"size_text", "10"});
    line1.properties = line1_property;
    parsed_ast_tree.push_back({"relation", line1});

    //fill line2
    line2.id1 = "dmnd";
    line2.id2 = "rctngl";
    line2.arrow = "->";
    line2_property.push_back({"text", "here is line2"});
    line2_property.push_back({"x", "10"}); 
    line2_property.push_back({"y", "12"}); 
    line2_property.push_back({"color", "NONE"});
    line2_property.push_back({"border", "3"});
    line2_property.push_back({"size_text", "8"});
    line2.properties = line2_property;
    parsed_ast_tree.push_back({"relation", line2});

    //fill line3
    line3.id1 = "crcl";
    line3.id2 = "dmnd";
    line3.arrow = "--";
    line3_property.push_back({"text", "here is line3"});
    line3_property.push_back({"x", "5"}); 
    line3_property.push_back({"y", "6"}); 
    line3_property.push_back({"color", "BLACK"});
    line3_property.push_back({"border", "2"});
    line3_property.push_back({"size_text", "10"});
    line3.properties = line3_property;
    parsed_ast_tree.push_back({"relation", line3});

    Translator tr;
    FiguresStorage result_tree = tr.translate(parsed_ast_tree);

    // check line1
    Shape* shape = result_tree[0];
    REQUIRE(shape);
    REQUIRE(shape->text == "here is line1");
    REQUIRE(style_helper::colorToString(shape->style.color) == "RED");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 4);
    REQUIRE(shape->y == 3);

    Line* line1AfterTranslate = dynamic_cast<Line*>(result_tree[0]);
    REQUIRE(line1AfterTranslate);
    REQUIRE(line1AfterTranslate->idFrom == "crcl");
    REQUIRE(line1AfterTranslate->idTo == "rctngl");
    REQUIRE(line1AfterTranslate->orientation == line_orientation_e::DoubleDirected);
    REQUIRE(line1AfterTranslate->type == line_type_e::Dotted);

    // check line2
    shape = result_tree[1];
    REQUIRE(shape);
    REQUIRE(shape->text == "here is line2");
    REQUIRE(style_helper::colorToString(shape->style.color) == "NONE");
    REQUIRE(shape->style.border == 3);
    REQUIRE(shape->style.textSize == 8);
    REQUIRE(shape->x == 10);
    REQUIRE(shape->y == 12);

    Line* line2AfterTranslate = dynamic_cast<Line*>(result_tree[1]);
    REQUIRE(line2AfterTranslate);
    REQUIRE(line2AfterTranslate->idFrom == "dmnd");
    REQUIRE(line2AfterTranslate->idTo == "rctngl");
    REQUIRE(line2AfterTranslate->orientation == line_orientation_e::Directed);
    REQUIRE(line2AfterTranslate->type == line_type_e::Solid);

    // check line3
    shape = result_tree[2];
    REQUIRE(shape);
    REQUIRE(shape->text == "here is line3");
    REQUIRE(style_helper::colorToString(shape->style.color) == "BLACK");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 5);
    REQUIRE(shape->y == 6);

    Line* line3AfterTranslate = dynamic_cast<Line*>(result_tree[2]);
    REQUIRE(line3AfterTranslate);
    REQUIRE(line3AfterTranslate->idFrom == "crcl");
    REQUIRE(line3AfterTranslate->idTo == "dmnd");
    REQUIRE(line3AfterTranslate->orientation == line_orientation_e::Undirected);
    REQUIRE(line3AfterTranslate->type == line_type_e::Dotted);
}

TEST_CASE("Translate note", "[Translator]"){
    std::vector<std::pair<std::string, std::any>> parsed_ast_tree;

    SEMANTICANALYZER::Note note1, note2;

    std::vector<SEMANTICANALYZER::Property> note1_property, note2_property;

    //fill note1
    note1.id = "nt1";
    note1_property.push_back({"text", "here is note1"});
    note1_property.push_back({"x", "4"}); 
    note1_property.push_back({"y", "3"}); 
    note1_property.push_back({"color", "PURPLE"});
    note1_property.push_back({"border", "2"});
    note1_property.push_back({"size_text", "10"});
    note1.properties = note1_property;
    parsed_ast_tree.push_back({"note", note1});

    //fill note2
    note2.id = "nt2";
    note2_property.push_back({"text", "here is note2"});
    note2_property.push_back({"x", "5"}); 
    note2_property.push_back({"y", "6"}); 
    note2_property.push_back({"color", "YELLOW"});
    note2_property.push_back({"border", "2"});
    note2_property.push_back({"size_text", "10"});
    note2.properties = note2_property;
    parsed_ast_tree.push_back({"note", note2});

    Translator tr;
    FiguresStorage result_tree = tr.translate(parsed_ast_tree);

    //check note1
    Shape* shape = result_tree[0];
    REQUIRE(shape);
    REQUIRE(shape->text == "here is note1");
    REQUIRE(style_helper::colorToString(shape->style.color) == "PURPLE");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 4);
    REQUIRE(shape->y == 3);

    Note* note1AfterTranslate = dynamic_cast<Note*>(result_tree[0]);
    REQUIRE(note1AfterTranslate);

    //check note1
    shape = result_tree[1];
    REQUIRE(shape);
    REQUIRE(shape->text == "here is note2");
    REQUIRE(style_helper::colorToString(shape->style.color) == "YELLOW");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 5);
    REQUIRE(shape->y == 6);

    Note* note2AfterTranslate = dynamic_cast<Note*>(result_tree[1]);
    REQUIRE(note2AfterTranslate);

}

TEST_CASE("Translate graph", "[Translator]"){
    std::vector<std::pair<std::string, std::any>> parsed_ast_tree;

    SEMANTICANALYZER::Graph graph;
    std::vector<SEMANTICANALYZER::Property> graph_property;
    std::vector<SEMANTICANALYZER::ObjectDecl> graph_objects;
    std::vector<SEMANTICANALYZER::Relation> graph_relations;
    //fill graph
    graph.id = "gr";
    graph_property.push_back({"text", "here is graph"});
    graph_property.push_back({"x", "4"}); 
    graph_property.push_back({"y", "3"}); 
    graph_property.push_back({"color", "BLACK"});
    graph_property.push_back({"border", "2"});
    graph_property.push_back({"size_text", "10"});
    graph.properties = graph_property;

    SEMANTICANALYZER::ObjectDecl circle, rectangle, diamond;
    std::vector<SEMANTICANALYZER::Property> circle_property, rectangle_property, diamond_property;
    // fill circle
    circle.id = "crcl";
    circle.shape = "circle";
    circle_property.push_back({"text", "here is circle"});
    circle_property.push_back({"x", "4"}); 
    circle_property.push_back({"y", "3"}); 
    //no color in circle
    circle_property.push_back({"border", "2"});
    circle_property.push_back({"size_text", "10"});
    circle_property.push_back({"radius", "5"});
    circle.properties = circle_property;
    // fill rectangle 
    rectangle.id = "rctngl";
    rectangle.shape = "rectangle";
    rectangle_property.push_back({"text", "here is rectangle"});
    rectangle_property.push_back({"x", "8"});
    rectangle_property.push_back({"y", "9"});
    rectangle_property.push_back({"color", "BLUE"});
    rectangle_property.push_back({"border", "2"});
    rectangle_property.push_back({"size_text", "10"});
    rectangle_property.push_back({"size_A", "3"});
    rectangle_property.push_back({"size_B", "4"});
    rectangle.properties = rectangle_property;
    // fill diamond 
    diamond.id = "dmnd";
    diamond.shape = "diamond";
    diamond_property.push_back({"text", "here is diamond"});
    diamond_property.push_back({"x", "8"});
    diamond_property.push_back({"y", "9"});
    diamond_property.push_back({"color", "NONE"});
    diamond_property.push_back({"border", "2"});
    diamond_property.push_back({"size_text", "10"});
    diamond_property.push_back({"size_A", "6"});
    diamond_property.push_back({"size_B", "4"});
    diamond_property.push_back({"angle","75"});
    diamond.properties = diamond_property;
    //add object vector
    graph_objects.push_back(circle);
    graph_objects.push_back(rectangle);
    graph_objects.push_back(diamond);
    graph.objects = graph_objects;

    SEMANTICANALYZER::Relation line1, line2;
    std::vector<SEMANTICANALYZER::Property> line1_property, line2_property;
    //fill line1
    line1.id1 = "crcl";
    line1.id2 = "rctngl";
    line1.arrow = "<-->";
    line1_property.push_back({"text", "here is line1"});
    line1_property.push_back({"x", "4"}); 
    line1_property.push_back({"y", "3"}); 
    line1_property.push_back({"color", "RED"});
    line1_property.push_back({"border", "2"});
    line1_property.push_back({"size_text", "10"});
    line1.properties = line1_property;
    //fill line2
    line2.id1 = "dmnd";
    line2.id2 = "rctngl";
    line2.arrow = "->";
    line2_property.push_back({"text", "here is line2"});
    line2_property.push_back({"x", "10"}); 
    line2_property.push_back({"y", "12"}); 
    //no color line2
    line2_property.push_back({"border", "3"});
    line2_property.push_back({"size_text", "8"});
    line2.properties = line2_property;
    //add object vector
    graph_relations.push_back(line1);
    graph_relations.push_back(line2);
    graph.relations = graph_relations;

    parsed_ast_tree.push_back({"graph", graph});
    Translator tr;
    FiguresStorage result_tree = tr.translate(parsed_ast_tree);

    //check graph
    Shape* shape = result_tree[0];
    REQUIRE(shape);
    REQUIRE(shape->text == "here is graph");
    REQUIRE(style_helper::colorToString(shape->style.color) == "BLACK");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 4);
    REQUIRE(shape->y == 3);

    Graph* graphAfterTranslate = dynamic_cast<Graph*>(result_tree[0]);
    REQUIRE(graphAfterTranslate);
    std::vector<Shape*> graph_obj_after_translate = graphAfterTranslate->nodes;

    Shape* _circle = graph_obj_after_translate[0];
    REQUIRE(graphAfterTranslate->style.border == _circle->style.border);
    REQUIRE(graphAfterTranslate->style.textSize == _circle->style.textSize);
    REQUIRE(graphAfterTranslate->style.color == _circle->style.color);

    Shape* _rectangle = graph_obj_after_translate[1];
    REQUIRE(graphAfterTranslate->style.border == _rectangle->style.border);
    REQUIRE(graphAfterTranslate->style.textSize == _rectangle->style.textSize);
    REQUIRE(_rectangle->style.color == color_e::BLUE);

    Shape* _line1 = graph_obj_after_translate[3];
    REQUIRE(graphAfterTranslate->style.border == _line1->style.border);
    REQUIRE(graphAfterTranslate->style.textSize == _line1->style.textSize);
    REQUIRE(_line1->style.color == color_e::RED);

    Shape* _line2 = graph_obj_after_translate[4];
    REQUIRE(_line2->style.border == 3);
    REQUIRE(_line2->style.textSize == 8);
    REQUIRE(graphAfterTranslate->style.color == _line2->style.color);
}

TEST_CASE("Translate dot_cloud", "[Translator]"){
    std::vector<std::pair<std::string, std::any>> parsed_ast_tree;

    SEMANTICANALYZER::DotCloud dot_cloud;
    std::vector<SEMANTICANALYZER::Property> dot_cloud_property;
    //fill DotCloud
    dot_cloud.id = "dc";
    dot_cloud_property.push_back({"text", "here is dot_cloud"});
    dot_cloud_property.push_back({"x", "4"}); 
    dot_cloud_property.push_back({"y", "3"}); 
    dot_cloud_property.push_back({"color", "BLACK"});
    dot_cloud_property.push_back({"border", "2"});
    dot_cloud_property.push_back({"size_text", "10"});
    dot_cloud_property.push_back({"grid", "true"});
    dot_cloud.externalProperties = dot_cloud_property;

    SEMANTICANALYZER::Dot dot1, dot2;
    std::vector<SEMANTICANALYZER::Property> dot1_property, dot2_property;
    // fill dot1
    dot1_property.push_back({"text", "here is dot1"});
    dot1_property.push_back({"x", "6"}); 
    dot1_property.push_back({"y", "4"}); 
    // no color dot1 => become BLACK
    dot1_property.push_back({"border", "2"});
    dot1_property.push_back({"size_text", "4"});
    dot1.internalProperties = dot1_property;
    dot_cloud.dots.push_back(dot1);

    // fill dot2
    dot2_property.push_back({"text", "here is dot2"});
    dot2_property.push_back({"x", "7"}); 
    dot2_property.push_back({"y", "1"}); 
    dot2_property.push_back({"color", "YELLOW"});
    dot2_property.push_back({"border", "3"});
    dot2_property.push_back({"size_text", "3"});
    dot2.internalProperties = dot2_property;
    dot_cloud.dots.push_back(dot2);

    parsed_ast_tree.push_back({"dot_cloud", dot_cloud});
    Translator tr;
    FiguresStorage result_tree = tr.translate(parsed_ast_tree);

    //check dot_cloud
    Shape* shape = result_tree[0];
    REQUIRE(shape);
    REQUIRE(shape->text == "here is dot_cloud");
    REQUIRE(style_helper::colorToString(shape->style.color) == "BLACK");
    REQUIRE(shape->style.border == 2);
    REQUIRE(shape->style.textSize == 10);
    REQUIRE(shape->x == 4);
    REQUIRE(shape->y == 3);

    DotCloud* dotCloudAfterTranslate = dynamic_cast<DotCloud*>(result_tree[0]);
    REQUIRE(dotCloudAfterTranslate->grid == true);
    REQUIRE(dotCloudAfterTranslate);
    std::vector<Circle*> dotCloud_obj_after_translate = dotCloudAfterTranslate->dots;

    Shape* _dot1 = dotCloud_obj_after_translate[0];
    REQUIRE(_dot1->style.border == 2);
    REQUIRE(_dot1->style.textSize == 4);
    REQUIRE(dotCloudAfterTranslate->style.color == _dot1->style.color);

    Shape* _dot2 = dotCloud_obj_after_translate[1];
    REQUIRE(_dot2->style.border == 3);
    REQUIRE(_dot2->style.textSize == 3);
    REQUIRE(_dot2->style.color == color_e::YELLOW);
}