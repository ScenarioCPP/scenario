#-------------------------------------------------
#
#
#-------------------------------------------------

include(../../common/support.pri)
TARGET = game03
TEMPLATE = app

HEADERS += \
    mainscene.h

SOURCES += \
    mainscene.cpp

INCLUDEPATH += \
    ../../common/vendor/Box2D \
    ../../common/vendor/Box2D/Box2D

