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
else:unix: LIBS += -L$$PWD/../../build/Common/Retranslator/src -lRetranslator \
                -L$$PWD/../../build/Common/AST/src -lAST \
                -L$$PWD/../../build/Common/Figures -lFigures \
                -L$$PWD/../../build/Common/FiguresStorage/src -lFiguresStorage \
                -L$$PWD/../../build/Common/Logger/src -lLogger \
                -L$$PWD/../../build/Common/SemanticAnalyzer/src -lSemanticAnalyzer \
                -L$$PWD/../../build/Common/FileManager/src -lFileManager

INCLUDEPATH += $$PWD/../../Common/Retranslator/src \
               $$PWD/../../Common/AST/src \
               $$PWD/../../Common/Figures \
               $$PWD/../../Common/FiguresStorage/src \
               $$PWD/../../Common/Logger/src \
               $$PWD/../../Common/SemanticAnalyzer/src \
               $$PWD/../../Common/FileManager/src

DEPENDPATH += $$PWD/../../Common/SemanticAnalyzer/src
