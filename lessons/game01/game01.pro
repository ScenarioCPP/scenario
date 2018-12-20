#-------------------------------------------------
#
#
#-------------------------------------------------
message(compiling in $$shell_path($$OUT_PWD))

include(../../common/support.pri)
TARGET = game01
TEMPLATE = app

HEADERS += \
    mainscene.h

SOURCES += \
    mainscene.cpp

