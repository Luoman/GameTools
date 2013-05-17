#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T14:34:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MapBox.cpp \
    TextureArea.cpp \
    WindowCreate.cpp \
    ImageManager.cpp \
    RoomDisplay.cpp \
    Room.cpp \
    MapDisplay.cpp \
    MAp.cpp \
    Object.cpp \
    Monster.cpp \
    Event.cpp \
    Door.cpp \
    XMLParse.cpp \
    XML/tools.cpp \
    XML/tinyxmlparser.cpp \
    XML/tinyxmlerror.cpp \
    XML/tinyxml.cpp \
    XML/tinystr.cpp \
    HelpWindow.cpp

HEADERS  += mainwindow.h \
    MapBox.h \
    TextureArea.h \
    WindowCreate.h \
    Convert.hh \
    ImageManager.h \
    Singleton.hh \
    RoomDisplay.h \
    MapDisplay.hh \
    Map.hh \
    Room.hh \
    Object.h \
    Monster.h \
    Event.h \
    Door.h \
    XMLParse.hh \
    XML/tools.h \
    XML/tinyxml.h \
    XML/tinystr.h \
    HelpWindow.h

FORMS    += mainwindow.ui
