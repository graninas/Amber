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
    ambermechanics.cpp \
    qambersurroundingstablemodel.cpp \
    naming.cpp \
    storms.cpp \
    strings.cpp

HEADERS  += shadowsview.h \
    amber.h \
    magic.h \
    common.h \
    knownareas.h \
    amberpolearea.h \
    naming.h \
    shadowmechanics.h \
    ambermechanics.h \
    monads.h \
    maybemonad.h \
    monadicvalue.h \
    functionalutils.h \
    qambersurroundingstablemodel.h \
    amberstructure.h \
    storms.h \
    lenses.h \
    strings.h

FORMS    += shadowsview.ui

RESOURCES += \
    Icons.qrc
