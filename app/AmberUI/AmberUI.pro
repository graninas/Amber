#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T21:19:42
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmberUI
TEMPLATE = app

CONFIG += c++14

FORMS    += shadowsview.ui

RESOURCES += \
    Icons.qrc


SOURCES += \
    main.cpp \
    shadowsview.cpp

HEADERS += \
    shadowsview.h

include($$PWD/../../lib/cpp_functional_core/cpp_functional_core.pri)
include($$PWD/../../lib/cpp_monads/cpp_monads.pri)
include($$PWD/../../src/amber/amber.pri)
