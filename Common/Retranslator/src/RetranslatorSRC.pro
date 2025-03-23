# AST lib
TEMPLATE = lib
TARGET = Retranslator

QT += core

CONFIG += c++17
CONFIG += plugin

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

SOURCES += Retranslator.cpp

HEADERS += Retranslator.hpp

INCLUDEPATH += ../../AST/src ../../Figures