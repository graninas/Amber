#-------------------------------------------------
#
# Project created by QtCreator 2014-11-10T21:19:42
#
#-------------------------------------------------

QT       += core gui
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/cpp_functional_core/release/ -lcpp_functional_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/cpp_functional_core/debug/ -lcpp_functional_core
else:unix: LIBS += -L$$OUT_PWD/../../lib/cpp_functional_core/ -lcpp_functional_core

INCLUDEPATH += $$PWD/../../lib/cpp_functional_core
DEPENDPATH += $$PWD/../../lib/cpp_functional_core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/release/libcpp_functional_core.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/debug/libcpp_functional_core.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/release/cpp_functional_core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/debug/cpp_functional_core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_functional_core/libcpp_functional_core.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../lib/cpp_monads/cpp_monads/release/ -lcpp_monads
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../lib/cpp_monads/cpp_monads/debug/ -lcpp_monads
else:unix: LIBS += -L$$OUT_PWD/../../lib/cpp_monads/cpp_monads/ -lcpp_monads

INCLUDEPATH += $$PWD/../../lib/cpp_monads/cpp_monads
DEPENDPATH += $$PWD/../../lib/cpp_monads/cpp_monads

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/release/libcpp_monads.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/debug/libcpp_monads.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/release/cpp_monads.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/debug/cpp_monads.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../lib/cpp_monads/cpp_monads/libcpp_monads.a

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
