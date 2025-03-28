# FileManager lib
TEMPLATE = lib
TARGET = FileManager

QT += core

CONFIG += c++17
CONFIG += plugin

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

SOURCES += FileManager.cpp

HEADERS += FileManager.hpp

INCLUDEPATH += ../../Logger/src
