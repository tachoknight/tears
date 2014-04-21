# Common config file for tests

QT       += testlib

QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DESTDIR = $$OUT_PWD/../binaries

include(link-sodium.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libtears/release/ -ltears
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libtears/debug/ -ltears
else:unix: LIBS += -L$$OUT_PWD/../../libtears/ -ltears

INCLUDEPATH += $$PWD/../../libtears
DEPENDPATH += $$PWD/../../libtears

INCLUDEPATH += $$PWD/../libtears/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libtears/release/libtears.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libtears/debug/libtears.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libtears/release/tears.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libtears/debug/tears.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libtears/libtears.a
