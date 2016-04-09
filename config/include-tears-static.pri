# Common config file for tests

QT       += testlib

QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

# Qt on the Mac assumes that pkg-config isn't installed,
# so this will force it
mac:QT_CONFIG -= no-pkg-config

TEMPLATE = app

DESTDIR = $$OUT_PWD/../binaries

include(link-sodium.pri)

CONFIG(sharedlib) {
LIBENDING = "so"
win32: LIBENDING = "dll"
}

!CONFIG(sharedlib) {
LIBENDING = "a"
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../libtears/ -ltears
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../libtears/ -ltears
else:unix: LIBS += -L$$OUT_PWD/../../libtears/ -ltears

INCLUDEPATH += $$PWD/../../libtears
DEPENDPATH += $$PWD/../../libtears
INCLUDEPATH += $$PWD/../libtears/include
$LD_LIBRARY_PATH = $$PWD/../../libtears:$LD_LIBRARY_PATH
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libtears/libtears.$$LIBENDING
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libtears/debug/libtears.$$LIBENDING
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libtears/release/tears.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libtears/debug/tears.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../libtears/libtears.$$LIBENDING
