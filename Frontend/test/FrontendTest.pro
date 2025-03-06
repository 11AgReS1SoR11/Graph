# Frontend's tests
TEMPLATE = app
TARGET = FrontendTest

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../build/Frontend/src -lFrontend

QT += testlib core

SOURCES += test.cpp

HEADERS += ../src/Frontend.hpp

INCLUDEPATH +=../src
