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
};

void TestClass::test_objectDecl()
{
    std::unordered_map<std::string, Shape*> map;
    Circle circle;
    circle.text = "circleTEXT";
    circle.x = 1;
    circle.y = 1;

    Shape* circle_ptr = &circle;
    map["circleID"] = circle_ptr;

    ASTTree tree(Retranslator::getInstance().parseTree(map));
    auto it = tree.begin();
    QVERIFY(it->getValue() == "root");
    ++it;
    QVERIFY(it->getValue() == "STARTGRAPH");
    ++it;
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
    QVERIFY(it->getValue() == "ENDGRAPH");
}


QTEST_GUILESS_MAIN(TestClass)
#include "RetranslatorTest.moc"
