#-------------------------------------------------
#
# Project created by QtCreator 2012-10-20T16:51:26
#
#-------------------------------------------------

QT       += core gui
TARGET = RiverModelGUI

SOURCES += view/mainwindow.cpp \
    view/configuration.cpp \
    view/modelthread.cpp \
    view/progressthread.cpp \
    view/imagethread.cpp

HEADERS  += view/mainwindow.h \
    view/configuration.h \
    view/modelthread.h \
    view/progressthread.h \
    view/imagethread.h

FORMS    += view/mainwindow.ui

include(./QmakeIncludes/RiverModelCommon.pri)
