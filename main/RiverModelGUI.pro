#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T16:51:26
#
#-------------------------------------------------

QT       += core gui

TARGET = RiverModelGUI
TEMPLATE = app


SOURCES += main.cpp \
    model/globals.cpp \
    model/cleanup.cpp \
    model/color.cpp \
    model/dump.cpp \
    model/go.cpp \
    model/patch.cpp \
    model/pred.cpp \
    model/setup.cpp \
    view/mainwindow.cpp \
    view/configuration.cpp \
    view/modelthread.cpp

HEADERS  += main.h \
    model/cleanup.h \
    model/color.h \
    model/dump.h \
    model/globals.h \
    model/go.h \
    model/patch.h \
    model/pred.h \
    model/setup.h \
    view/mainwindow.h \
    view/configuration.h \
    view/modelthread.h

FORMS    += view/mainwindow.ui
