#-------------------------------------------------
#
# Project created by QtCreator 2013-03-08T23:45:59
#
#-------------------------------------------------

TARGET = DeleteOldFiles

TEMPLATE = app

QT       += core gui widgets

CONFIG += c++11

RC_FILE = DeleteOldFiles.rc

HEADERS  += \
    src/MessagesWidget.hpp \
    src/DirectoryGuide.hpp \
    src/FileRemover.hpp \
    src/Application.hpp \
    src/MainWindow.hpp \
    src/DirectoryTreeRemover.hpp \
    src/DirectoryTreeRemoverThread.hpp \
    src/Icons.hpp \
    src/MessagesTreeWidget.hpp

SOURCES += \
	src/main.cpp\
	src/MessagesWidget.cpp \
	src/DirectoryGuide.cpp \
	src/FileRemover.cpp \
	src/Application.cpp \
	src/MainWindow.cpp \
	src/DirectoryTreeRemover.cpp \
	src/DirectoryTreeRemoverThread.cpp \
	src/Icons.cpp \
	src/MessagesTreeWidget.cpp

RESOURCES += \
	src/Images.qrc

OTHER_FILES += \
	src/DeleteOldFiles.rc \
    gpl.txt

CONFIG(debug, debug|release): LIBS += -L$$PWD/../CppAidKit/build/Debug/ -lAidKit
CONFIG(release, debug|release): LIBS += -L$$PWD/../CppAidKit/build/Release/ -lAidKit

INCLUDEPATH += $$PWD/../CppAidKit/headers
DEPENDPATH += $$PWD/../CppAidKit/sources
