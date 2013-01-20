TEMPLATE = app
win32:CONFIG += static

SOURCES += main.cpp \
    model/rivermodel.cpp \
    model/status.cpp \
    model/globals.cpp \
    model/cleanup.cpp \
    model/color.cpp \
    model/dump.cpp \
    model/go.cpp \
    model/patch.cpp \
    model/pred.cpp \
    model/setup.cpp \
    model/hydrofile.cpp \
    model/hydrofiledict.cpp \
    model/carbonflowmap.cpp \

HEADERS  += model/rivermodel.h \
    model/status.h \
    model/cleanup.h \
    model/color.h \
    model/dump.h \
    model/globals.h \
    model/go.h \
    model/patch.h \
    model/pred.h \
    model/setup.h \
    model/grid.h \
    model/hydrofile.h \
    model/hydrofiledict.h \
    model/carbonflowmap.h \


# Update your personal (projctDir)/.git/info/excludes file if you alter SettingsOverrides
include(./SettingsOverrides.pri)
