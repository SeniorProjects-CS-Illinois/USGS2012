#Compiles a version of Rivermodel without a gui interface

TARGET = RiverModel
DESTDIR = ./
CONFIG += console
DEFINES += NO_GUI

include(./QmakeIncludes/RiverModelCommon.pri)
