#-------------------------------------------------
#
#
#-------------------------------------------------

include(../../common/support.pri)
TARGET = game02
TEMPLATE = app

HEADERS += \
    mainscene.h

SOURCES += \
    mainscene.cpp

INCLUDEPATH += \
    ../../common/vendor/Chipmunk2D/include
LIBS += -L../../common/vendor/Chipmunk2D/build/src -lchipmunk
QMAKE_LFLAGS += '-Wl,-rpath,../../../../../common/vendor/Chipmunk2D/build/src/'
