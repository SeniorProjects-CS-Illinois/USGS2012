QT+= testlib

CONFIG += testcase

TARGET = runTests

SOURCES +=  ../main/model/reducedgrid.cpp \
            ../main/model/configuration.cpp \

DEPENDPATH += . \
              ../main \

INCLUDEPATH += ../main/model

# Input
SOURCES += TestClass.cpp \
