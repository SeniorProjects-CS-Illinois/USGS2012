TEMPLATE = app
win32:CONFIG += static

#QMAKE_CXXFLAGS += -fopenmp
#LIBS += -fopenmp

QMAKE_CXXFLAGS += -pg
QMAKE_LFLAGS += -pg

SOURCES += model/cleanup.cpp \
    model/color.cpp \
    model/configuration.cpp \
    model/dump.cpp \
    model/globals.cpp \
    model/go.cpp \
    model/hydrofile.cpp \
    model/hydrofiledict.cpp \
    model/patch.cpp \
    model/patchcollection.cpp \
    model/patchcomputation.cpp \
    model/pred.cpp \
    model/reducedgrid.cpp \
    model/river.cpp \
    model/rivermodel.cpp \
    model/setup.cpp \
    model/status.cpp \
    model/utility.cpp \

HEADERS  += model/cleanup.h \
    model/color.h \
    model/configuration.h \
    model/constants.h \
    model/dump.h \
    model/flowdata.h \
    model/globals.h \
    model/go.h \
    model/grid.h \
    model/hydrofile.h \
    model/hydrofiledict.h \
    model/patch.h \
    model/patchcollection.h \
    model/patchcomputation.h \
    model/pred.h \
    model/reducedgrid.h \
    model/river.h \
    model/rivermodel.h \
    model/setup.h \
    model/status.h \
    model/utility.h \


# Update your personal (projctDir)/.git/info/excludes file if you alter SettingsOverrides
include(./SettingsOverrides.pri)
