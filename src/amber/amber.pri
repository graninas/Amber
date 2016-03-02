win32:      CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/amber/release/ -lamber
else:win32: CONFIG(debug, debug|release):   LIBS += -L$$OUT_PWD/../../src/amber/debug/   -lamber
else:unix:                                  LIBS += -L$$OUT_PWD/../../src/amber/         -lamber

INCLUDEPATH += $$PWD/../../src/amber
DEPENDPATH  += $$PWD/../../src/amber

win32-g++:             CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/release/libamber.a
else:win32-g++:        CONFIG(debug, debug|release):   PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/debug/libamber.a
else:win32:!win32-g++: CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/release/amber.lib
else:win32:!win32-g++: CONFIG(debug, debug|release):   PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/debug/amber.lib
else:unix:                                             PRE_TARGETDEPS += $$OUT_PWD/../../src/amber/libamber.a

