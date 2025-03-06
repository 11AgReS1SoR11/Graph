#include <QtTest/QtTest>
#include "Frontend.hpp"

class TestClass : public QObject
{
    Q_OBJECT

    void someTest();
};

void TestClass::someTest()
{
    /*
    TODO: implement
    */
    frontend::Frontend front;
    QVERIFY(&front);
}

QTEST_GUILESS_MAIN(TestClass)
#include "test.moc"
