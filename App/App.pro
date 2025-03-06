# Application
TEMPLATE = app
TARGET = Graph

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

LIBS += -L$$PWD/../build/Frontend/src -lFrontend
LIBS += -L$$PWD/../build/Backend/src -lBackend

QT += core

SOURCES += main.cpp

INCLUDEPATH += ../Frontend/src
