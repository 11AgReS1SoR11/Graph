QT -= gui

TEMPLATE = lib
DEFINES += SEMANTICANALYZER_LIBRARY

CONFIG += c++17

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
    AstStatementParser.cpp \
    SemanticAnalyzer.cpp

HEADERS += \
    AstStatementParser.h \
    SemanticAnalyzer.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../AST/src/release/ -lAST
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../AST/src/debug/ -lAST
else:unix: LIBS += -L$$OUT_PWD/../../AST/src/ -lAST

INCLUDEPATH += $$PWD/../../AST/src
DEPENDPATH += $$PWD/../../AST/src


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Logger/src/release/ -lLogger
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Logger/src/debug/ -lLogger
else:unix: LIBS += -L$$OUT_PWD/../../Logger/src/ -lAST

INCLUDEPATH += $$PWD/../../Logger/src
DEPENDPATH += $$PWD/../../Logger/src


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
