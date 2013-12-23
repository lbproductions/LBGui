#-------------------------------------------------
#
# Project created by QtCreator 2013-12-23T12:41:39
#
#-------------------------------------------------

QT       += widgets

TARGET = mainwindowtest

TEMPLATE = app


SOURCES += \
    main.cpp


macx: LIBS += -L$$OUT_PWD/../src/ -lLBGui

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

macx: PRE_TARGETDEPS += $$OUT_PWD/../src/libLBGui.a
