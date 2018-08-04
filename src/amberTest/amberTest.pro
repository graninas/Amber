#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:13:52
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = tst_ambertest
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++1z

TEMPLATE = app

SOURCES += tst_ambertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../lib/cpp_stm/cpp_stm.pri)
include($$PWD/../../src/amber/amber.pri)
