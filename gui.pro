QT += core widgets
TARGET = program
TEMPLATE = app

SOURCES = src/*.cpp
HEADERS = src/*.h
INCLUDEPATH += src

OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = rcc

RESOURCES += resources.qrc

CONFIG += compile_commands

