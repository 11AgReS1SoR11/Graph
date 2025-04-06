#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "FiguresStorage.hpp"
#include "Figures.hpp"




bool compareShape(Shape const& first, Shape const& second)
{
    return first.id == second.id && first.text == second.text && first.x == second.x && first.y == second.y
            && first.style.border == second.style.border && first.style.color == second.style.color &&
            first.style.textSize == second.style.textSize;
}


void checkCircle(Shape* shape, Circle& circle)
{
    Circle* circleFromJson = dynamic_cast<Circle*>(shape);
    REQUIRE(circleFromJson);
    REQUIRE(compareShape(*circleFromJson, circle));
    REQUIRE(circleFromJson->radius == circle.radius);
}

void checkDiamond(Shape* shape, Diamond& diamond)
{
    Diamond* diamondFromJson = dynamic_cast<Diamond*>(shape);
    REQUIRE(diamondFromJson);
    REQUIRE(compareShape(*diamondFromJson, diamond));
    REQUIRE(diamondFromJson->sizeA == diamond.sizeA);
    REQUIRE(diamondFromJson->sizeB == diamond.sizeB);
    REQUIRE(diamondFromJson->angle == diamond.angle);

}

void checkRectangle(Shape* shape, Rectangle& rectangle)
{
    Rectangle* rectangleFromJson = dynamic_cast<Rectangle*>(shape);
    REQUIRE(rectangleFromJson);
    REQUIRE(compareShape(*rectangleFromJson, rectangle));
    REQUIRE(rectangleFromJson->sizeA == rectangle.sizeA);
    REQUIRE(rectangleFromJson->sizeB == rectangle.sizeB);
}

void checkLine(Shape* shape, Line& line)
{
    Line* lineFromJson = dynamic_cast<Line*>(shape);
    REQUIRE(lineFromJson);
    REQUIRE(compareShape(*lineFromJson, line));
    REQUIRE(lineFromJson->idFrom == line.idFrom);
    REQUIRE(lineFromJson->idTo == line.idTo);
    REQUIRE(lineFromJson->orientation == line.orientation);
    REQUIRE(lineFromJson->type == line.type);
}

TEST_CASE("Creates simpe figures", "[FiguresStorage]")
{
    Circle circle;
    Rectangle rectangle;
    Diamond diamond;
    Line line;
    Note note;

    std::string const json = getJsonFromFigures({&circle, &rectangle, &diamond, &line, &note});

    FiguresStorage figures = FiguresStorage::createFigures(json);
    REQUIRE(figures.size() == 5);

    checkCircle(figures[0], circle);
    checkRectangle(figures[1], rectangle);
    checkDiamond(figures[2], diamond);
    checkLine(figures[3], line);

    // check Note
    Note* noteFromJson = dynamic_cast<Note*>(figures[4]);
    REQUIRE(noteFromJson);
    REQUIRE(compareShape(*noteFromJson, note));
    REQUIRE(noteFromJson->idTo == note.idTo);
    REQUIRE(noteFromJson->sizeA == note.sizeA);
    REQUIRE(noteFromJson->sizeB == note.sizeB);
}


TEST_CASE("Creates graph", "[FiguresStorage]")
{
    Circle circle;
    Rectangle rectangle;
    Diamond diamond;
    Line line;

    Graph graph;
    graph.nodes.push_back(&circle);
    graph.nodes.push_back(&rectangle);
    graph.nodes.push_back(&diamond);
    graph.nodes.push_back(&line);

    std::string const json = getJsonFromFigures({&graph});

    FiguresStorage figures = FiguresStorage::createFigures(json);
    REQUIRE(figures.size() == 1);

    Graph* graphFromJson = dynamic_cast<Graph*>(figures[0]);

    REQUIRE(graphFromJson);
    REQUIRE(compareShape(*graphFromJson, graph));

    checkCircle(graphFromJson->nodes[0], circle);
    checkRectangle(graphFromJson->nodes[1], rectangle);
    checkDiamond(graphFromJson->nodes[2], diamond);
    checkLine(graphFromJson->nodes[3], line);
}

TEST_CASE("Creates DotCloud", "[FiguresStorage]")
{
    Circle circle1;
    Circle circle2;
    Circle circle3;

    DotCloud dotCloud;
    dotCloud.dots.push_back(&circle1);
    dotCloud.dots.push_back(&circle2);
    dotCloud.dots.push_back(&circle3);

    std::string const json = getJsonFromFigures({&dotCloud});

    FiguresStorage figures = FiguresStorage::createFigures(json);
    REQUIRE(figures.size() == 1);

    DotCloud* dotcloudFromJson = dynamic_cast<DotCloud*>(figures[0]);

    REQUIRE(dotcloudFromJson);
    REQUIRE(compareShape(*dotcloudFromJson, dotCloud));

    checkCircle(dotcloudFromJson->dots[0], circle1);
    checkCircle(dotcloudFromJson->dots[1], circle2);
    checkCircle(dotcloudFromJson->dots[2], circle3);
}