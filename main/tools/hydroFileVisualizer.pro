#Compiles a version of Rivermodel without a gui interface

TARGET = HydroFileVisualizer
DESTDIR = ./
CONFIG += console
TEMPLATE = app
SOURCES += hydrofilevisualizer.cpp \
    ../model/hydrofile.cpp \
    ../model/grid.cpp

HEADERS  += ../model/hydrofile.h \
    ../model/grid.h \

