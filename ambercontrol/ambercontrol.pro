#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:23:20
#
#-------------------------------------------------

QT       -= core gui

TARGET = ambercontrol
TEMPLATE = lib
CONFIG += staticlib

SOURCES += ambercontrol.cpp \
    magic.cpp \
    naming.cpp \
    strings.cpp

HEADERS += ambercontrol.h \
    knownareas.h \
    magic.h \
    naming.h \
    strings.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
