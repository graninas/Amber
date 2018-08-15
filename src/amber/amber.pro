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

SOURCES += amber.cpp \
    model/helpers.cpp \
    model/transactions.cpp \
    assets/world1.cpp

HEADERS += amber.h \
    model/helpers.h \
    model/model.h \
    model/transactions.h \
    assets/world1.h

OTHER_FILES += \
    amber.pri

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../lib/cpp_stm/cpp_stm.pri)
