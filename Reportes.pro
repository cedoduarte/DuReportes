#-------------------------------------------------
#
# Project created by QtCreator 2015-05-20T16:20:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reportes
TEMPLATE = app


SOURCES += main.cpp \
        Widget.cpp

HEADERS  += Widget.h

FORMS    += Widget.ui

QMAKE_CXXFLAGS += -std=gnu++14

include($$PWD/QtRptProject/QtRPT/QtRPT.pri)

RESOURCES += \
    res.qrc
