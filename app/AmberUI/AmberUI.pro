#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T21:19:42
#
#-------------------------------------------------

QT       += core gui
include(../../defaults.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmberUI
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

FORMS    += shadowsview.ui

RESOURCES += \
    Icons.qrc


SOURCES += \
    main.cpp \
    qambersurroundingstablemodel.cpp \
    shadowsview.cpp

HEADERS += \
    presentationsnippets.h \
    qambersurroundingstablemodel.h \
    shadowsview.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/amber/release/ -lamber
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/amber/debug/ -lamber
else:unix: LIBS += -L$$OUT_PWD/../../src/amber/ -lamber

INCLUDEPATH += $$PWD/../../src/amber
DEPENDPATH += $$PWD/../../src/amber

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/release/libamber.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/debug/libamber.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/release/amber.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/debug/amber.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/libamber.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/monad/monad/release/ -lmonad
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/monad/monad/debug/ -lmonad
else:unix: LIBS += -L$$OUT_PWD/../../lib/monad/monad/ -lmonad

INCLUDEPATH += $$PWD/../../lib/functional_core
DEPENDPATH += $$PWD/../../lib/functional_core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/release/libfunctional_core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/debug/libfunctional_core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/release/functional_core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/debug/functional_core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/functional_core/libfunctional_core.a


INCLUDEPATH += $$PWD/../../lib/monad/monad
DEPENDPATH += $$PWD/../../lib/monad/monad

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/release/libmonad.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/debug/libmonad.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/release/monad.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/debug/monad.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/monad/monad/libmonad.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/functional_core/release/ -lfunctional_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/functional_core/debug/ -lfunctional_core
else:unix: LIBS += -L$$OUT_PWD/../../lib/functional_core/ -lfunctional_core
