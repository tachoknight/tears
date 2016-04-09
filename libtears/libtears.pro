#-------------------------------------------------
#
# Project created by QtCreator 2014-04-11T14:32:25
#
#-------------------------------------------------

QT -= gui
QT += core
mac:QT_CONFIG -= no-pkg-config

TARGET = tears
TEMPLATE = lib

!CONFIG(sharedlib) {
CONFIG += staticlib
message(Making static lib)
}

HEADERS += include/tears.hpp \
    include/tears/crypto.hpp \
    include/tears/util.hpp \
    include/tears/hashing.hpp \
    include/tears/publickeycrypto.hpp \
    include/tears/export.hpp

SOURCES += \
    src/crypto.cpp \
    src/util.cpp \
    src/hashing.cpp \
    src/publickeycrypto.cpp

INCLUDEPATH += $$PWD/include/

include(../config/link-sodium.pri)

DEFINES += TEARS_LIBRARY
