### General config ###

TARGET          = LBGui
VERSION         = 0.0.1
TEMPLATE        = lib
QT              += sql
CONFIG          += static c++11

QT              += sql widgets

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    childwidget.h

SOURCES += \
    mainwindow.cpp \
    childwidget.cpp

RESOURCES += \
    ../resources/uiresources.qrc

