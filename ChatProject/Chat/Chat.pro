#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T18:54:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chatwidget.cpp \
    mainmenuwidget.cpp \
    clientwidget.cpp \
    serverwidget.cpp

HEADERS  += mainwindow.h \
    chatwidget.h \
    mainmenuwidget.h \
    clientwidget.h \
    serverwidget.h

DISTFILES +=

RESOURCES += \
    rsc.qrc
