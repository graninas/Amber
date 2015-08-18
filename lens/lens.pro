#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T22:56:58
#
#-------------------------------------------------

QT       -= core gui

TARGET = lens
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++14

SOURCES +=

HEADERS += \
    example.h \
    identity.h \
    lenses.h \
    autolens.h \
    combinators.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
