#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T21:19:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmberUI
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        shadowsview.cpp \
    amber.cpp \
    magic.cpp \
    shadowmechanics.cpp \
    amberpolearea.cpp \
    ambermechanics.cpp

HEADERS  += shadowsview.h \
    amber.h \
    magic.h \
    common.h \
    shadowstructure.h \
    knownareas.h \
    amberpolearea.h \
    naming.h \
    shadowmechanics.h \
    ambermechanics.h \
    monads.h \
    maybemonad.h \
    monadicvalue.h \
    functionalutils.h

FORMS    += shadowsview.ui

RESOURCES += \
    Icons.qrc
