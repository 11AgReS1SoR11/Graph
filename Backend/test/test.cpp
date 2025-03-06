#include <QtTest/QtTest>
#include "Backend.hpp"

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
    backend::Backend back;
    QVERIFY(&back);
}

QTEST_GUILESS_MAIN(TestClass)
#include "test.moc"
