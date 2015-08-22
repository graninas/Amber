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
    identity.h \
    lenses.h \
    autolens.h \
    fold.h \
    setter.h \
    getter.h \
    lens_stack.h \
    lens.h \
    bind_combinator.h \
    to_combinator.h \
    traversed.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
