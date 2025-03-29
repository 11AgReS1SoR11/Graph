QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

SOURCES +=  \
    SemanticAnalyzerTest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lSemanticAnalyzer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lSemanticAnalyzer
else:unix: LIBS += -L$$OUT_PWD/../src/ -lSemanticAnalyzer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../AST/src/release/ -lAST
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../AST/src/debug/ -lAST
else:unix: LIBS += -L$$OUT_PWD/../../AST/src/ -lAST

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

INCLUDEPATH += $$PWD/../../AST/src
DEPENDPATH += $$PWD/../../AST/src
