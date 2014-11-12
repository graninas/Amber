#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T22:05:14
#
#-------------------------------------------------

QT       -= gui

TARGET = Shadows
TEMPLATE = lib

DEFINES += SHADOWS_LIBRARY

SOURCES += shadows.cpp

HEADERS += shadows.h\
        shadows_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
