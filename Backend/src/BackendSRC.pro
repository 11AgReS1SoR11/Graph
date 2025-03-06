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
