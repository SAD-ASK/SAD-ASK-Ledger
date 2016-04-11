TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    times.cpp \
    stats.cpp \
    core.cpp \
    profile.cpp

HEADERS += \
    times.h \
    main.h \
    globals.h \
    core.h \
    profile.h

DISTFILES += \
    TODO \
    NOTES \
    README.md

