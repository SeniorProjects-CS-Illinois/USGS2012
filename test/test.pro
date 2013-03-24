QT+= testlib

CONFIG += testcase debug

TARGET = runTests

DEPENDPATH += . \
              ../main \

SOURCES += ../main/model/configuration.cpp \

INCLUDEPATH += ../main/model

# Input
HEADERS +=  GridTests.h \
            ReducedGridTests.h \
            ConfigTests.h \

SOURCES +=  TestMain.cpp \
            GridTests.cpp \
            ReducedGridTests.cpp \
            ConfigTests.cpp \
