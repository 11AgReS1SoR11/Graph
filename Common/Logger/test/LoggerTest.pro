# Logger's tests
TEMPLATE = app
TARGET = LoggerTest

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../../build/Common/Logger/src -lLogger

QT += testlib core

SOURCES += test.cpp

HEADERS += ../src/Logger.hpp

INCLUDEPATH += ../src
