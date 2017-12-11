#-------------------------------------------------
#
# Project created by QtCreator 2017-09-24T18:54:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chatwidget.cpp \
    mainmenuwidget.cpp \
    clientwidget.cpp \
    serverwidget.cpp \
    ../ChatServer/chatserver.cpp \
    ../ChatClient/chatclient.cpp \
    sidemenu.cpp

HEADERS  += mainwindow.h \
    chatwidget.h \
    mainmenuwidget.h \
    clientwidget.h \
    serverwidget.h \
    ../ChatServer/chatserver.h \
    ../ChatClient/chatclient.h \
    sidemenu.h

DISTFILES +=

RESOURCES += \
    rsc.qrc
