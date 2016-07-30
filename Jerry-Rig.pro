#-------------------------------------------------
#
# Project created by QtCreator 2016-07-27T15:19:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Jerry-Rig
TEMPLATE = app


SOURCES += main.cpp\
        mainmenu.cpp \
    settingmenu.cpp \
    processmanager.cpp

HEADERS  += mainmenu.h \
    settingmenu.h \
    processmanager.h \
    convparams.h

FORMS    += mainmenu.ui \
    settingmenu.ui \
    processmanager.ui


RESOURCES += \
    icons.qrc
