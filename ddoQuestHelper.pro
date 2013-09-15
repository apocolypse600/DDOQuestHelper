#-------------------------------------------------
#
# Project created by QtCreator 2013-09-15T14:05:16
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ddoQuestHelper
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    comboboxdelegate.cpp

HEADERS  += mainwindow.h \
    comboboxdelegate.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    ddoQuestDatabase.db \
    ddoQuestHelper.ini
