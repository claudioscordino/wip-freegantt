#-------------------------------------------------
#
# Project created by QtCreator 2013-03-08T11:37:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FreeGantt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    project.cpp \
    task.cpp \
    resource.cpp

HEADERS  += mainwindow.hpp \
    project.hpp \
    task.hpp \
    resource.hpp

FORMS    += mainwindow.ui

OTHER_FILES += \
    freegantt.qrc
