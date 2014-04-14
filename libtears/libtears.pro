#-------------------------------------------------
#
# Project created by QtCreator 2014-04-11T14:32:25
#
#-------------------------------------------------

QT       -= gui
QT += core

TARGET = tears
TEMPLATE = lib
CONFIG += staticlib

HEADERS += include/tears.hpp \
    include/tears/crypto.hpp \
    include/tears/util.hpp

SOURCES += \
    src/crypto.cpp \
    src/util.cpp

INCLUDEPATH += $$PWD/include/

unix {
    target.path = /usr/lib
    INSTALLS += target

    # Include libsodium
    CONFIG += link_pkgconfig
    PKGCONFIG += libsodium
}

win32:DEFINES += WINDOWS
