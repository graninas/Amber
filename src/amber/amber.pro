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
    ambermechanics.cpp \
    amberpolearea.cpp \
    shadowmechanics.cpp \
    naming.cpp \
    event_log.cpp \
    storms.cpp \
    taskmechanics.cpp

HEADERS += amber.h \
    ambermechanics.h \
    amberpolearea.h \
    amberstructure.h \
    storms.h \
    amberfacade.h \
    shadowmechanics.h \
    knownareas.h \
    naming.h \
    event_log.h \
    taskmechanics.h \
    model/world_component.h

OTHER_FILES += \
    amber.pri

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include($$PWD/../../lib/cpp_functional_core/cpp_functional_core.pri)
include($$PWD/../../lib/cpp_monads/cpp_monads.pri)
include($$PWD/../../lib/cpp_stm/cpp_stm.pri)
