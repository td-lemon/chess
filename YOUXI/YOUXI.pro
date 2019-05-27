#-------------------------------------------------
#
# Project created by QtCreator 2017-05-02T08:56:46
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YOUXI
TEMPLATE = app


SOURCES += main.cpp\
    GameModel.cpp \
    start.cpp \
    mainwindow.cpp \
    liststack.cpp

HEADERS  += \
    GameModel.h \
    mainwindow.h \
    start.h \
    liststack.h

RESOURCES += \
    resoure.qrc

SUBDIRS += \
    ../../../qtÎå×ÓÆå/QtWuziqi/QtWuziqi.pro

