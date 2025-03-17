# Frontend lib
TEMPLATE = lib
TARGET = Frontend

QT += core widgets

CONFIG += c++17
CONFIG += plugin

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

SOURCES += Frontend.cpp \
           BaseWidget.cpp \
           GraphicsWidget.cpp \
           MainWindow.cpp \
           TextWidget.cpp

HEADERS += Frontend.hpp \
           BaseWidget.hpp \
           GraphicsWidget.hpp \
           MainWindow.hpp \
           TextWidget.hpp

INCLUDEPATH += ..
