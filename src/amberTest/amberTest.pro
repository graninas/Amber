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
QMAKE_CXXFLAGS += -nostdinc++

TEMPLATE = app

INCLUDEPATH += /usr/include/x86_64-linux-gnu/c++/7
INCLUDEPATH += /usr/include/c++/7

SOURCES += tst_ambertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../lib/cpp_functional_core/cpp_functional_core.pri)
include($$PWD/../../lib/cpp_monads/cpp_monads.pri)
include($$PWD/../../lib/cpp_stm/cpp_stm.pri)
