QT+= testlib

CONFIG += testcase

TARGET = runTests

DEPENDPATH += . \
              ../main \

SOURCES += ../main/model/configuration.cpp \

INCLUDEPATH += ../main/model

# Input
HEADERS +=  GridTests.h \
            ReducedGridTests.h \
            ConfigTests.h \

SOURCES +=  TestClass.cpp \
            GridTests.cpp \
            ReducedGridTests.cpp \
            ConfigTests.cpp \
