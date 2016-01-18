TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ledger.cpp \
    sqlite3.c \
    sqlite3.c

HEADERS += \
    ledger.h \
    sqlite3.h

DISTFILES += \
    TODO \
    NOTES \
    README.md

