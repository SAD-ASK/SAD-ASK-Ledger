TEMPLATE = app
CONFIG += console c++0x
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    times.cpp \
    stats.cpp \
    core.cpp \
    profile.cpp \
    input.cpp \
    help.cpp

HEADERS += \
    times.h \
    globals.h \
    core.h \
    profile.h \
    input.h \
    help.h

DISTFILES += \
    TODO \
    NOTES \
    README.md

