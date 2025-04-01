# FiguresStorage's tests
TEMPLATE = app
TARGET = FiguresStorageTest

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../../build/Common/FiguresStorage/src -lFiguresStorage
LIBS += -L$$PWD/../../../build/Common/Figures -lFigures
LIBS += -L$$PWD/../../../build/Common/Logger/src -lLogger

QT += testlib core

SOURCES += test.cpp

HEADERS += ../src/FiguresStorage.hpp

INCLUDEPATH += ../src \
               ../../Figures
