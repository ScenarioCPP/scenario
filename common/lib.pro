#-------------------------------------------------
#
# Project created by QtCreator 2018-11-21T08:35:39
#
#  Added AssetsManager, moved initialization to World
#
#-------------------------------------------------
macx{
QMAKE_POST_LINK = cp $$shell_path($$OUT_PWD)/*.dylib  ../common/lib/.
}
unix:!macx{
QMAKE_POST_LINK = cp $$shell_path($$OUT_PWD)/*.so  ../common/lib/.
}
win32 {
QMAKE_POST_LINK = copy $$shell_path($$OUT_PWD)\\*.dll ..\\common\\lib
}
QT += core gui
# Windows Arghh!!!!!
#QT += webenginewidgets
QT += multimedia multimediawidgets

TEMPLATE = lib
TARGET = ScenarioLib

DEFINES += SCENESHAREDLIB_LIBRARY
greaterThan(QT_MAJOR_VERSION, 4): QT += \
                                        widgets \
                                        svg \
                                        xml
CONFIG+=sdk_no_version_check

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG+=sdk_no_version_check
INCLUDEPATH += "$$PWD/include"

SOURCES += \
                $$PWD/src/world.cpp \
                $$PWD/src/actor.cpp \
                $$PWD/src/image.cpp \
                $$PWD/src/view.cpp \
                $$PWD/src/scene.cpp \
                $$PWD/src/text.cpp \
                $$PWD/src/svgengine.cpp \
                $$PWD/src/gameengine.cpp \
                $$PWD/src/controller.cpp \
                $$PWD/src/sprite.cpp \
                $$PWD/src/viewwidget.cpp \
                $$PWD/src/assetsmanager.cpp \
                $$PWD/src/tileset.cpp \
                $$PWD/src/frame.cpp \
                $$PWD/src/settingsdialog.cpp \
                $$PWD/src/portal.cpp \
                $$PWD/src/tilemapdialog.cpp \
                $$PWD/src/paths.cpp \
                $$PWD/src/helpdialog.cpp \
                $$PWD/src/animator.cpp \
                $$PWD/src/collider.cpp \
                $$PWD/src/playerfactory.cpp \
                $$PWD/src/npcfactory.cpp \
                $$PWD/src/pcharacter.cpp \
                $$PWD/src/npcharacter.cpp \
                $$PWD/src/carrot.cpp \
                $$PWD/src/sequentialguid.cpp \
                $$PWD/src/scenario.cpp \
                $$PWD/src/scenariomanager.cpp \
    $$PWD/src/shape.cpp \
    $$PWD/src/circle.cpp

HEADERS += \
                $$PWD/include/world.h \
                $$PWD/include/actor.h \
                $$PWD/include/image.h \
                $$PWD/include/view.h \
                $$PWD/include/scene.h \
                $$PWD/include/text.h \
                $$PWD/include/svgengine.h \
                $$PWD/include/gameengine.h \
                $$PWD/include/controller.h \
                $$PWD/include/sprite.h \
                $$PWD/include/viewwidget.h \
                $$PWD/include/collider.h \
                $$PWD/include/assetsmanager.h \
                $$PWD/include/tileset.h \
                $$PWD/include/frame.h \
                $$PWD/include/animator.h \
                $$PWD/include/settingsdialog.h \
                $$PWD/include/portal.h \
                $$PWD/include/tilemapdialog.h \
                $$PWD/include/paths.h \
                $$PWD/include/helpdialog.h \
                $$PWD/include/iactorfactory.h \
                $$PWD/include/playerfactory.h \
                $$PWD/include/npcfactory.h \
                $$PWD/include/pcharacter.h \
                $$PWD/include/npcharacter.h \
                $$PWD/include/icharacter.h \
                $$PWD/include/carrot.h \
                $$PWD/include/global_defines.h \
                $$PWD/include/sequentialguid.h \
                $$PWD/include/scenario.h \
                $$PWD/include/scenariomanager.h \
                $$PWD/include/shape.h \
                $$PWD/include/circle.h

FORMS += \
                $$PWD/forms/tilemapdialog.ui \
                $$PWD/forms/helpdialog.ui


