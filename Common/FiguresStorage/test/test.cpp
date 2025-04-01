#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "FiguresStorage.hpp"
#include "Figures.hpp"

std::string getJsonFromFigures(std::vector<Shape*> const& figures)
{
    std::string json = "[";
    for (Shape* figure : figures)
    {
        json += figure->toJson() + ",";
    }
    json += "]";

    return json;
}

bool compareShape(Shape const& first, Shape const& second)
{
    return first.id == second.id && first.text == second.text && first.x == second.x && first.y == second.y
            && first.style.border == second.style.border && first.style.color == second.style.color &&
            first.style.textSize == second.style.textSize;
}

TEST_CASE("Creates simpe figures", "[FiguresStorage]")
{
    Circle circle;
    Rectangle rectangle;
    Diamond diamond;
    Line line;

    std::string const json = getJsonFromFigures({&circle, &rectangle, &diamond, &line});

    FiguresStorage figures = FiguresStorage::createFigures(json);
    REQUIRE(figures.size() == 4);

    // check Circle
    Circle* circleFromJson = dynamic_cast<Circle*>(figures[0]);
    REQUIRE(circleFromJson);
    REQUIRE(compareShape(*circleFromJson, circle));
    REQUIRE(circleFromJson->radius == circle.radius);

    // check Rectangle
    Rectangle* rectangleFromJson = dynamic_cast<Rectangle*>(figures[1]);
    REQUIRE(rectangleFromJson);
    REQUIRE(compareShape(*rectangleFromJson, rectangle));
    REQUIRE(rectangleFromJson->sizeA == rectangle.sizeA);
    REQUIRE(rectangleFromJson->sizeB == rectangle.sizeB);

    // check Diamond
    Diamond* diamondFromJson = dynamic_cast<Diamond*>(figures[2]);
    REQUIRE(diamondFromJson);
    REQUIRE(compareShape(*diamondFromJson, diamond));
    REQUIRE(diamondFromJson->sizeA == diamond.sizeA);
    REQUIRE(diamondFromJson->sizeB == diamond.sizeB);
    REQUIRE(diamondFromJson->angle == diamond.angle);

    // check Line
    Line* lineFromJson = dynamic_cast<Line*>(figures[3]);
    REQUIRE(lineFromJson);
    REQUIRE(compareShape(*lineFromJson, line));
    REQUIRE(lineFromJson->idFrom == line.idFrom);
    REQUIRE(lineFromJson->idTo == line.idTo);
    REQUIRE(lineFromJson->orientation == line.orientation);
    REQUIRE(lineFromJson->type == line.type);
}
