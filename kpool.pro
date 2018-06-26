TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/arg_parser.cpp \
    src/utils.cpp \
    src/main.cpp \
    src/merger.cpp

HEADERS += \
    src/arg_parser.h \
    src/parameters.h \
    src/utils.h \
    src/merger.h
