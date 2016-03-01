TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    ledger.cpp \
    times.cpp

HEADERS += \
    ledger.h \
    times.h \
    main.h

DISTFILES += \
    TODO \
    NOTES \
    README.md

