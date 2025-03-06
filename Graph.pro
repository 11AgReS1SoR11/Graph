# Specify that this project is a collection of subprojects
TEMPLATE = subdirs

# Define the directories for the Frontend, Backend and include files
FRONTEND_DIR = Frontend
BACKEND_DIR = Backend
COMMON_DIR = Common
APP_DIR = App

# Add the subdirectories for the Frontend and Backend to SUBDIRS
SUBDIRS += $$FRONTEND_DIR \
           $$BACKEND_DIR \
           $$COMMON_DIR \
           $$APP_DIR \

CONFIG += ordered
