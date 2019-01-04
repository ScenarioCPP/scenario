#Y-------------------------------------------------
#
# Project created by QtCreator 2018-11-21T08:35:39
#
#  Added AssetsManager, moved initialization to World
#
#-------------------------------------------------

QT += core gui
# Windows Arghh!!!!!
#QT += webenginewidgets
QT += multimedia multimediawidgets

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
                $$PWD/src/main.cpp \
                $$PWD/src/mainwindow.cpp

HEADERS += \
                $$PWD/include/mainwindow.h
                $$PWD/include/ui_mainwindow.h

FORMS += \
                $$PWD/forms/mainwindow.ui
                $$PWD/forms/mainwindow.ui

RESOURCES += \
               $$PWD/resources/assets.qrc



DEPENDPATH += $$PWD//include


#unix{ QMAKE_POST_LINK = cp $$shell_path($$OUT_PWD)/../../common/lib/*.dylib  $$shell_path($$OUT_PWD/$$TARGET).app/Contents/MacOS/. }
QMAKE_LFLAGS += '-Wl,-rpath,../../../../../common/lib'

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lScenarioLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lScenarioLib
else:unix: LIBS += -L$$PWD/lib/ -lScenarioLib -lbox2d

