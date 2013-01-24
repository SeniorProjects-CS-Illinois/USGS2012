#Compiles a version of Rivermodel without a gui interface

TARGET = RiverModel
DESTDIR = ../
CONFIG += console

SOURCES += main.cpp

include(./QmakeIncludes/RiverModelCommon.pri)
