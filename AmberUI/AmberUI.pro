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
    qambersurroundingstablemodel.cpp

HEADERS  += \
    common.h \
    monads.h \
    maybemonad.h \
    functionalutils.h \
    qambersurroundingstablemodel.h \
    presentationsnippets.h \
    maybeactionstack.h

FORMS    += shadowsview.ui

RESOURCES += \
    Icons.qrc
