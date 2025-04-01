#include <QtTest/QtTest>
#include "FiguresStorage.hpp"
#include "Figures.hpp"

class TestClass : public QObject
{
    Q_OBJECT

    std::string getJsonFromFigures(std::vector<Shape*> const& figures);
    bool compareShape(Shape const& first, Shape const& second);

private slots:
    void test_createFromJsonWithSimpleFigures();
};

std::string TestClass::getJsonFromFigures(std::vector<Shape*> const& figures)
{
    std::string json = "[";
    for (Shape* figure : figures)
    {
        json += figure->toJson() + ",";
    }
    json += "]";

    return json;
}

bool TestClass::compareShape(Shape const& first, Shape const& second)
{
    return first.id == second.id && first.text == second.text && first.x == second.x && first.y == second.y
            && first.style.border == second.style.border && first.style.color == second.style.color &&
            first.style.textSize == second.style.textSize;
}

void TestClass::test_createFromJsonWithSimpleFigures()
{
    Circle circle;
    Reactangle reactangle;
    Diamond diamond;
    Line line;

    std::string const json = getJsonFromFigures({&circle, &reactangle, &diamond, &line});

    FiguresStorage figures = FiguresStorage::createFigures(json);
    QVERIFY(figures.size() == 4);

    // check Circle
    Circle* circleFromJson = dynamic_cast<Circle*>(figures[0]);
    QVERIFY(circleFromJson);
    QVERIFY(compareShape(*circleFromJson, circle));
    QVERIFY(circleFromJson->radius == circle.radius);

    // check Reactangle
    Reactangle* reactangleFromJson = dynamic_cast<Reactangle*>(figures[1]);
    QVERIFY(reactangleFromJson);
    QVERIFY(compareShape(*reactangleFromJson, reactangle));
    QVERIFY(reactangleFromJson->sizeA == reactangle.sizeA);
    QVERIFY(reactangleFromJson->sizeB == reactangle.sizeB);

    // check Diamond
    Diamond* diamondFromJson = dynamic_cast<Diamond*>(figures[2]);
    QVERIFY(diamondFromJson);
    QVERIFY(compareShape(*diamondFromJson, diamond));
    QVERIFY(diamondFromJson->sizeA == diamond.sizeA);
    QVERIFY(diamondFromJson->sizeB == diamond.sizeB);
    QVERIFY(diamondFromJson->angle == diamond.angle);

    // check Line
    Line* lineFromJson = dynamic_cast<Line*>(figures[3]);
    QVERIFY(lineFromJson);
    QVERIFY(compareShape(*lineFromJson, line));
    QVERIFY(lineFromJson->idFrom == line.idFrom);
    QVERIFY(lineFromJson->idTo == line.idTo);
    QVERIFY(lineFromJson->orientation == line.orientation);
    QVERIFY(lineFromJson->type == line.type);
}

QTEST_GUILESS_MAIN(TestClass)
#include "test.moc"
