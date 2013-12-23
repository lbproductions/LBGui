QPERSISTENCE_PATH = ../lib/QPersistence
include($$QPERSISTENCE_PATH/QPersistence.pri)

### General config ###

TARGET          = projectoptinvest
VERSION         = 0.0.1
TEMPLATE        = app
ICON            = icon.icns
QT              += sql widgets
CONFIG          += c++11
QMAKE_CXXFLAGS  += $$QPERSISTENCE_COMMON_QMAKE_CXXFLAGS


### Qp ###

INCLUDEPATH     += $$QPERSISTENCE_INCLUDEPATH
LIBS            += $$QPERSISTENCE_LIBS

SOURCES += \
    main.cpp \
    controller.cpp \
    data/customer.cpp


macx: LIBS += -L$$OUT_PWD/../lib/LBGui/src/ -lLBGui

INCLUDEPATH += $$PWD/../lib/LBGui/src
DEPENDPATH += $$PWD/../lib/LBGui/src

macx: PRE_TARGETDEPS += $$OUT_PWD/../lib/LBGui/src/libLBGui.a

HEADERS += \
    controller.h \
    data/customer.h
