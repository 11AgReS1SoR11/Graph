# Backend lib
TEMPLATE = lib
TARGET = Backend

QT += core

CONFIG += c++17
CONFIG += plugin

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

SOURCES += Backend.cpp

HEADERS += Backend.hpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Common/SemanticAnalyzer/src/release/ -lSemanticAnalyzer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Common/SemanticAnalyzer/src/debug/ -lSemanticAnalyzer
else:unix: LIBS += -L$$OUT_PWD/../../Common/SemanticAnalyzer/src/ -lSemanticAnalyzer

INCLUDEPATH += $$PWD/../../Common/SemanticAnalyzer/src
DEPENDPATH += $$PWD/../../Common/SemanticAnalyzer/src
