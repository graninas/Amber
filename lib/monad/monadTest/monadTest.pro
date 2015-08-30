#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T00:54:06
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_monadtest
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


SOURCES += tst_monadtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../monad/release/ -lmonad
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../monad/debug/ -lmonad
else:unix: LIBS += -L$$OUT_PWD/../monad/ -lmonad

INCLUDEPATH += $$PWD/../monad
DEPENDPATH += $$PWD/../monad

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../monad/release/libmonad.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../monad/debug/libmonad.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../monad/release/monad.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../monad/debug/monad.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../monad/libmonad.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../functional_core/release/ -lfunctional_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../functional_core/debug/ -lfunctional_core
else:unix: LIBS += -L$$OUT_PWD/../../functional_core/ -lfunctional_core

INCLUDEPATH += $$PWD/../../functional_core
DEPENDPATH += $$PWD/../../functional_core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../functional_core/release/libfunctional_core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../functional_core/debug/libfunctional_core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../functional_core/release/functional_core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../functional_core/debug/functional_core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../functional_core/libfunctional_core.a
