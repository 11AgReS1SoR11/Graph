# Figures lib
TEMPLATE = lib
TARGET = Figures

QT += core

CONFIG += c++17
CONFIG += plugin

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

SOURCES += Diamond.cpp \
           Circle.cpp \
           DotCloud.cpp \
           Graph.cpp \
           Line.cpp \
           Reactangle.cpp

HEADERS += Diamond.hpp \
           Circle.hpp \
           DotCloud.hpp \
           Graph.hpp \
           Line.hpp \
           Reactangle.hpp
