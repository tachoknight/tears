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
    include/tears/util.hpp \
    include/tears/hashing.hpp

SOURCES += \
    src/crypto.cpp \
    src/util.cpp \
    src/hashing.cpp

INCLUDEPATH += $$PWD/include/


include(../config/link-sodium.pri)

win32:DEFINES += WINDOWS
