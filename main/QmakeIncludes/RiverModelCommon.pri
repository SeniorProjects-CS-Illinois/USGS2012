TEMPLATE = app
win32:CONFIG += static

#QMAKE_CXXFLAGS += -fopenmp
#LIBS += -fopenmp

QMAKE_CXXFLAGS += -pg
QMAKE_LFLAGS += -pg

SOURCES += model/rivermodel.cpp \
    model/status.cpp \
    model/globals.cpp \
    model/cleanup.cpp \
    model/color.cpp \
    model/dump.cpp \
    model/go.cpp \
    model/patch.cpp \
    model/patchCollection.cpp \
    model/pred.cpp \
    model/river.cpp \
    model/setup.cpp \
    model/hydrofile.cpp \
    model/hydrofiledict.cpp \
    model/configuration.cpp \
    model/reducedgrid.cpp \

HEADERS  += model/rivermodel.h \
    model/status.h \
    model/cleanup.h \
    model/color.h \
    model/constants.h \
    model/dump.h \
    model/flowdata.h \
    model/globals.h \
    model/go.h \
    model/patch.h \
    model/patchCollection.h \
    model/pred.h \
    model/river.h \
    model/setup.h \
    model/grid.h \
    model/hydrofile.h \
    model/hydrofiledict.h \
    model/configuration.h \
    model/reducedgrid.h \


# Update your personal (projctDir)/.git/info/excludes file if you alter SettingsOverrides
include(./SettingsOverrides.pri)
