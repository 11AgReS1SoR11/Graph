#include "Logger.hpp"

#include <QtTest/QtTest>
#include <QFile>
#include <QTextStream>
#include <QVector>

class TestLogger : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testLoggingToFile();
    void cleanupTestCase();

private:
    QString readLastLogLine();
};

static QVector<QString> const LOGS = {"Info log", "Warn log", "Error log"};
static QString const LOG_FORMAT_STR = "[%1][%2] %3";

void TestLogger::initTestCase()
{
    QFile file(LOG_FILE_PATH);
    if (file.exists())
    {
        file.remove();
    }
}

void TestLogger::testLoggingToFile()
{
    {
        LOG_INFO(FRONTEND_LOG, LOGS[0]);
        QString const lastLog = readLastLogLine();
        QVERIFY(lastLog.contains(LOG_FORMAT_STR.arg("INFO").arg(FRONTEND_LOG).arg(LOGS[0])));
    }

    {
        LOG_WARN(BACKEND_LOG, LOGS[1]);
        QString const lastLog = readLastLogLine();
        QVERIFY(lastLog.contains(LOG_FORMAT_STR.arg("WARN").arg(BACKEND_LOG).arg(LOGS[1])));
    }

    {
        LOG_ERROR(TRANSLATOR_LOG, LOGS[2]);
        QString const lastLog = readLastLogLine();
        QVERIFY(lastLog.contains(LOG_FORMAT_STR.arg("ERROR").arg(TRANSLATOR_LOG).arg(LOGS[2])));
    }
}

void TestLogger::cleanupTestCase()
{
    QFile::remove(LOG_FILE_PATH);
}

QString TestLogger::readLastLogLine()
{
    QFile file(LOG_FILE_PATH);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QString();
    }

    QTextStream in(&file);
    QString lastLine;
    while (!in.atEnd())
    {
        lastLine = in.readLine();
    }
    
    file.close();
    return lastLine;
}

QTEST_MAIN(TestLogger)
#include "test.moc"
