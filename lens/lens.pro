#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T22:56:58
#
#-------------------------------------------------

QT       -= core gui

TARGET = lens
TEMPLATE = lib
CONFIG += staticlib

SOURCES += lens.cpp

HEADERS += \
    example.h \
    lenses.h \
    identity.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
