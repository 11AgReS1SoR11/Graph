# AST's tests
TEMPLATE = app
TARGET = RetranslatorTest

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../../build/Common/Retranslator/src -lRetranslator

QT += testlib core

SOURCES += RetranslatorTest.cpp

HEADERS += ../src/Retranslator.hpp

INCLUDEPATH +=../src ../../AST/src ../../Figures
