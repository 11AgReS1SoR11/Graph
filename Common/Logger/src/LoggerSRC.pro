# Logger lib
TEMPLATE = lib
TARGET = Logger

QT += core

CONFIG += c++17
CONFIG += plugin

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

SOURCES += Logger.cpp

HEADERS += Logger.hpp
