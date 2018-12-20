#-------------------------------------------------
#
#
#-------------------------------------------------
#message(compiling in $$shell_path($$OUT_PWD))

# pull in all of the common support libraries and startup
include(../../common/support.pri)

TARGET = step01
TEMPLATE = app

HEADERS += \
    mainscene.h

SOURCES += \
    mainscene.cpp

