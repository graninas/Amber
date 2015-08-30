#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:09:19
#
#-------------------------------------------------

QT -= core gui

TARGET = amber
TEMPLATE = lib
CONFIG += staticlib

QMAKE_CXXFLAGS += -std=c++11

SOURCES += amber.cpp \
    ambermechanics.cpp \
    amberpolearea.cpp \
    magic.cpp \
    shadowmechanics.cpp \
    naming.cpp \
    event_log.cpp \
    storms.cpp

HEADERS += amber.h \
    ambermechanics.h \
    amberpolearea.h \
    amberstructure.h \
    storms.h \
    amberfacade.h \
    magic.h \
    shadowmechanics.h \
    knownareas.h \
    naming.h \
    event_log.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/functional_core/release/ -lfunctional_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/functional_core/debug/ -lfunctional_core
else:unix: LIBS += -L$$OUT_PWD/../../lib/functional_core/ -lfunctional_core

INCLUDEPATH += $$PWD/../../lib/functional_core
DEPENDPATH += $$PWD/../../lib/functional_core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/release/libfunctional_core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/debug/libfunctional_core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/release/functional_core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/debug/functional_core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/libfunctional_core.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/monad/monad/release/ -lmonad
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/monad/monad/debug/ -lmonad
else:unix: LIBS += -L$$OUT_PWD/../../lib/monad/monad/ -lmonad

INCLUDEPATH += $$PWD/../../lib/monad/monad
DEPENDPATH += $$PWD/../../lib/monad/monad

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/release/libmonad.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/debug/libmonad.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/release/monad.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/debug/monad.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/libmonad.a
