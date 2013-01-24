#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T16:51:26
#
#-------------------------------------------------

QT       += core gui
TARGET = RiverModelGUI
DESTDIR = ../

SOURCES += view/mainwindow.cpp \
    view/configuration.cpp \
    view/modelthread.cpp \
    view/progressthread.cpp \
    util/files.cpp \
    util/ui.cpp \
    util/hydromaps.cpp \
    mainGUI.cpp

HEADERS  += view/mainwindow.h \
    view/configuration.h \
    view/modelthread.h \
    view/progressthread.h \
    util/files.h \
    util/ui.h \
    util/hydromaps.h

FORMS    += view/mainwindow.ui

include(./QmakeIncludes/RiverModelCommon.pri)
