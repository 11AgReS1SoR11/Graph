#include <QtTest/QtTest>
#include "FileManager.hpp"
#include <QFile>

class TestFileManager : public QObject
{
    Q_OBJECT

private slots:
    void testWriteToFile();
    void testReadFromFile();
    void testFileExistsAfterWrite();
    void testReadNonExistentFile();
    void testOverwriteFile();
};

static QString const FILE_PATH = "build/test_file.txt";

void TestFileManager::testWriteToFile()
{
    QVERIFY(FileManager::writeToFile(FILE_PATH.toStdString(), "Hello, QtTest!"));
}

void TestFileManager::testReadFromFile()
{
    QString const dataWrite = "Test Read";
    auto const success = FileManager::writeToFile(FILE_PATH.toStdString(), dataWrite.toStdString());
    QVERIFY(success);

    auto const res = FileManager::readFromFile(FILE_PATH.toStdString());
    QVERIFY(res);

    QCOMPARE(QString::fromStdString(*res), dataWrite);
}

void TestFileManager::testFileExistsAfterWrite()
{
    auto const success = FileManager::writeToFile("build/Such_file_non_exist", "Checking existence");
    QVERIFY(success);

    QFile file(FILE_PATH);
    QVERIFY(file.exists());
}

void TestFileManager::testReadNonExistentFile()
{
    auto const res = FileManager::readFromFile("Lalala");
    QVERIFY(!res);
}

void TestFileManager::testOverwriteFile()
{
    QString const lastData = "Second write";
    auto success = FileManager::writeToFile(FILE_PATH.toStdString(), "First write");
    QVERIFY(success);

    success = FileManager::writeToFile(FILE_PATH.toStdString(), lastData.toStdString());
    QVERIFY(success);

    auto const res = FileManager::readFromFile(FILE_PATH.toStdString());
    QVERIFY(res);
    QCOMPARE(QString::fromStdString(*res), lastData);
}

QTEST_GUILESS_MAIN(TestFileManager)
#include "test.moc"
