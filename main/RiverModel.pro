#Compiles a version of Rivermodel without a gui interface

TARGET = RiverModel
DESTDIR = ./
TEMPLATE = app

CONFIG -= qt
CONFIG += console

DEFINES += NO_GUI

SOURCES += main.cpp \
    model/globals.cpp \
    model/cleanup.cpp \
    model/color.cpp \
    model/dump.cpp \
    model/go.cpp \
    model/patch.cpp \
    model/pred.cpp \
    model/setup.cpp \
    lib/libpng/libpng.cpp

HEADERS  += main.h \
    model/cleanup.h \
    model/color.h \
    model/dump.h \
    model/globals.h \
    model/go.h \
    model/patch.h \
    model/pred.h \
    model/setup.h 

LIBS += -lpng
