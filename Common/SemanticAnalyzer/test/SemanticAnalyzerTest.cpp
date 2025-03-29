#include <QtTest>

#include "SemanticAnalyzer.h"
#include "AstStatementParser.h"

class SemanticAnalyzerTest : public QObject
{
    Q_OBJECT

public:
    SemanticAnalyzerTest() = default;
    ~SemanticAnalyzerTest() = default;

private slots:
    void test_cases();

};


void SemanticAnalyzerTest::test_cases()
{

}

QTEST_APPLESS_MAIN(SemanticAnalyzerTest)

#include "SemanticAnalyzerTest.moc"
