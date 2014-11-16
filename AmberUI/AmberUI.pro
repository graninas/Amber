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
    shadows.cpp \
    amber.cpp \
    magic.cpp \
    assets.cpp \
    shadowstructure.cpp \
    shadowmechanics.cpp

HEADERS  += shadowsview.h \
    amber.h \
    shadows.h \
    magic.h \
    common.h \
    assets.h \
    shadowstructure.h \
    knownareas.h \
    amberpolearea.h \
    naming.h \
    shadowmechanics.h

FORMS    += shadowsview.ui

RESOURCES += \
    Icons.qrc
