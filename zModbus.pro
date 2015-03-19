#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T14:17:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zModbus
TEMPLATE = app


SOURCES += main.cpp\
        zmodbus.cpp \
    modbusexample.cpp

HEADERS  += zmodbus.h \
    modbusexample.h

FORMS    += \
    modbusexample.ui

DISTFILES += \
    functionCodes.txt
