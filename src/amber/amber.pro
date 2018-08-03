#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:09:19
#
#-------------------------------------------------

QT -= core gui

TARGET = amber
TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++1z
QMAKE_CXXFLAGS += -nostdinc++

INCLUDEPATH += /usr/include/x86_64-linux-gnu/c++/7
INCLUDEPATH += /usr/include/c++/7

SOURCES += amber.cpp \
    model/helpers.cpp \
    model/transactions.cpp

HEADERS += amber.h \
    model/helpers.h \
    model/model.h \
    model/transactions.h

OTHER_FILES += \
    amber.pri

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../lib/cpp_stm/cpp_stm.pri)
