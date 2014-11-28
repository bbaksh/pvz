#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T14:59:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pvz_bbaksh
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    usermanagement.cpp \
    gameplay.cpp \
    gamedisplay.cpp \
    plants.cpp \
    zombies.cpp \
    sun.cpp \
    bullets.cpp \
    lawnmower.cpp

HEADERS  += mainwindow.h \
    usermanagement.h \
    gameplay.h \
    gamedisplay.h \
    plants.h \
    zombies.h \
    sun.h \
    bullets.h \
    lawnmower.h

FORMS    += mainwindow.ui
