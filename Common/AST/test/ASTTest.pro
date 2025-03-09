# AST's tests
TEMPLATE = app
TARGET = ASTTest

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../../build/Common/AST/src -lAST

QT += testlib core

SOURCES += test.cpp

HEADERS += ../src/AST.hpp

INCLUDEPATH +=../src
