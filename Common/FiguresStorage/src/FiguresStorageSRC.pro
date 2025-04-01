# FiguresStorage lib
TEMPLATE = lib
TARGET = FiguresStorage

QT += core

CONFIG += c++17
CONFIG += plugin

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../../../build/Common/Figures -lFigures
LIBS += -L$$PWD/../../../build/Common/Logger/src -lLogger

SOURCES += FiguresStorage.cpp

HEADERS += FiguresStorage.hpp

INCLUDEPATH += ../../Figures \
               ../../Logger/src
