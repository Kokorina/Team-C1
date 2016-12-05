#-------------------------------------------------
#
# Project created by QtCreator 2016-07-19T15:28:32
#
#-------------------------------------------------

CONFIG   += c++11
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = csv-converter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CsvFile.cpp \
    csvRow.cpp \
    toolparentclass.cpp \
    toolsubclass.cpp \
    tool.cpp

HEADERS  += mainwindow.h \
    CsvFile.h \
    csvRow.h \
    toolparentclass.h \
    toolsubclass.h \
    tool.h

FORMS    += mainwindow.ui
