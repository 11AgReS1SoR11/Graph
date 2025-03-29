# AST's tests
TEMPLATE = app
TARGET = RetranslatorTest

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../../build/Common/Retranslator/src -lRetranslator \
        -L$$PWD/../../../build/Common/AST/src -lAST \
        -L$$PWD/../../../build/Common/Figures -lFigures

QT += testlib core

SOURCES += RetranslatorTest.cpp

HEADERS += ../src/Retranslator.hpp

INCLUDEPATH +=../src ../../AST/src ../../Figures
