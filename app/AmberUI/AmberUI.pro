#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T21:19:42
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmberUI
TEMPLATE = app

CONFIG += c++1z

FORMS    += \
    amberview.ui

RESOURCES += \
    Icons.qrc


SOURCES += \
    main.cpp \
    amberview.cpp

HEADERS += \
    amberview.h \
    ui_helpers.h

include($$PWD/../../lib/cpp_stm/cpp_stm.pri)
include($$PWD/../../src/amber/amber.pri)
