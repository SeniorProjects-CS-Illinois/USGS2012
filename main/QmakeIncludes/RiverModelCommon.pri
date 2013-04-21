TEMPLATE = app

#QMAKE_CXXFLAGS += -fopenmp
#LIBS += -fopenmp

# Gprof flags for profiling the application.  Keep commented unless actively
# profiling the program.  You should also disable openmp when profiling
# otherwise the anaylsis will be inaccurate.
#QMAKE_CXXFLAGS += -pg
#QMAKE_LFLAGS += -pg

SOURCES += model/carbonflowmap.cpp \
    model/carbonsources.cpp \
    model/configuration.cpp \
    model/hydrofile.cpp \
    model/hydrofiledict.cpp \    
    model/patchcollection.cpp \
    model/patchcomputation.cpp \    
    model/reducedgrid.cpp \
    model/river.cpp \
    model/rivermodel.cpp \
    model/status.cpp \
    model/utility.cpp \

HEADERS  +=  model/carbonflowmap.h \
    model/carbonsources.h \
    model/configuration.h \
    model/constants.h \
    model/flowdata.h \
    model/grid.h \
    model/hydrodata.h \
    model/hydrofile.h \
    model/hydrofiledict.h \
    model/patchcollection.h \
    model/patchcomputation.h \
    model/reducedgrid.h \
    model/river.h \
    model/rivermodel.h \
    model/statistics.h \
    model/status.h \
    model/utility.h



# Update your personal (projctDir)/.git/info/excludes file if you alter SettingsOverrides
include(./SettingsOverrides.pri)
