# Application
TEMPLATE = app
TARGET = Graph

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../build/Frontend/src -lFrontend # TODO: remove
LIBS += -L$$PWD/../build/Common/Retranslator/src -lRetranslator \
        -L$$PWD/../build/Common/AST/src -lAST \
        -L$$PWD/../build/Common/Figures -lFigures \
        -L$$PWD/../build/Common/FiguresStorage/src -lFiguresStorage \
        -L$$PWD/../build/Common/Logger/src -lLogger \
        -L$$PWD/../build/Common/SemanticAnalyzer/src -lSemanticAnalyzer \
        -L$$PWD/../build/Common/FileManager/src -lFileManager \
        -L$$PWD/../build/Backend/src -lBackend

QT += core

SOURCES += main.cpp

INCLUDEPATH += ../Backend/src \
               ../Common/Logger/src
