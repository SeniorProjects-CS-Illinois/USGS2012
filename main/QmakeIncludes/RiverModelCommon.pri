TEMPLATE = app
win32:CONFIG += static

#QMAKE_CXXFLAGS += -fopenmp
#LIBS += -fopenmp

#QMAKE_CXXFLAGS += -pg
#QMAKE_LFLAGS += -pg

SOURCES += model/configuration.cpp \
    model/globals.cpp \    
    model/hydrofile.cpp \
    model/hydrofiledict.cpp \    
    model/patchcollection.cpp \
    model/patchcomputation.cpp \    
    model/reducedgrid.cpp \
    model/river.cpp \
    model/rivermodel.cpp \
    model/status.cpp \
    model/utility.cpp \

HEADERS  +=model/configuration.h \
    model/constants.h \
    model/flowdata.h \
    model/globals.h \
    model/grid.h \
    model/hydrofile.h \
    model/hydrofiledict.h \
    model/patchcollection.h \
    model/patchcomputation.h \
    model/reducedgrid.h \
    model/river.h \
    model/rivermodel.h \
    model/statistics.h \
    model/status.h \
    model/utility.h \


# Update your personal (projctDir)/.git/info/excludes file if you alter SettingsOverrides
include(./SettingsOverrides.pri)
