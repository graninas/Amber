#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T21:19:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmberUI
TEMPLATE = app


SOURCES += main.cpp\
        shadowsview.cpp \
    shadows.cpp

HEADERS  += shadowsview.h \
    amber.h \
    shadows.h

FORMS    += shadowsview.ui

RESOURCES += \
    Icons.qrc
