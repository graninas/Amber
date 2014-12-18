#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:09:19
#
#-------------------------------------------------

QT       -= core gui

TARGET = amber
TEMPLATE = lib
CONFIG += staticlib

SOURCES += amber.cpp \
    ambermechanics.cpp \
    amberpolearea.cpp

HEADERS += amber.h \
    ambermechanics.h \
    amberpolearea.h \
    amberstructure.h \
    storms.h \
    amberfacade.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
