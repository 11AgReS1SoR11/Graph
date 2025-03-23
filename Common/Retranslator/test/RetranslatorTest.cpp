#include <QtTest/QtTest>
#include <stdexcept>

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
    circle.text = "circle";
    circle.x = 1;
    circle.y = 1;

    Shape* circle_ptr = &circle;
    map["circle"] = circle_ptr;

    ASTTree tree(Retranslator::getInstance().parseTree(map));
    auto it = tree.begin();
    QVERIFY(it->getValue() == "root");
}