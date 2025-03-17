# Frontend
TEMPLATE = subdirs

# Add the subdirectories for the sources and tests to SUBDIRS
SUBDIRS += src/FrontendSRC.pro \
           test/FrontendTest.pro

# Adding a custom command to the build: copy the Resource folder to build/Frontend/src
copydata.commands = $(COPY_DIR) $$PWD/utils/Resources $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
