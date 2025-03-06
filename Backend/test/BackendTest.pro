# Backend's tests
TEMPLATE = app
TARGET = BackendTest

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../build/Backend/src -lBackend

QT += testlib core

SOURCES += test.cpp

HEADERS += ../src/Backend.hpp

INCLUDEPATH +=../src
