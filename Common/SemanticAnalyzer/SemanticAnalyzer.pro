QT -= gui

TEMPLATE = lib
DEFINES += SEMANTICANALYZER_LIBRARY

CONFIG += c++20

CONFIG += plugin

# Build dirs
OBJECTS_DIR = objects
MOC_DIR     = objects
UI_DIR      = objects
RCC_DIR     = objects

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += SEMANTICANALYZER_EXPORTS

SOURCES += \
    SemanticAnalyzer.cpp

HEADERS += \
    SemanticAnalyzer.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
