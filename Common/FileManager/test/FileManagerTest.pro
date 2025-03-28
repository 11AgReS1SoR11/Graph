# FileManager's tests
TEMPLATE = app
TARGET = FileManagerTest

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../../build/Common/FileManager/src -lFileManager
LIBS += -L$$PWD/../../../build/Common/Logger/src -lLogger

QT += testlib core

SOURCES += test.cpp

HEADERS += ../src/FileManager.hpp

INCLUDEPATH += ../src
