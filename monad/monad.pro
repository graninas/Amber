#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:26:49
#
#-------------------------------------------------

QT       -= core gui

TARGET = monad
TEMPLATE = lib

DEFINES += MONAD_LIBRARY

SOURCES += monad.cpp

HEADERS += monad.h\
        monad_global.h \
    functionalutils.h \
    maybeactionstack.h \
    maybemonad.h \
    monads.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
