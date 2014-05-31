#-------------------------------------------------
#
# Project created by QtCreator 2013-03-08T23:45:59
#
#-------------------------------------------------

QT       += core gui widgets

CONFIG += c++11

TARGET = DeleteOldFiles
TEMPLATE = app

RC_FILE = DeleteOldFiles.rc

SOURCES += src/main.cpp\
	src/MessagesWidget.cpp \
	src/DirectoryGuide.cpp \
	src/FileRemover.cpp \
	src/Application.cpp \
	src/MainWindow.cpp \
	src/DirectoryTreeRemover.cpp \
	src/DirectoryTreeRemoverThread.cpp \
	src/Icons.cpp \
	src/MessagesTreeWidget.cpp \
	src/PERA/PERA_AboutDialog.cpp \
	src/PERA/PERA_Application.cpp \
	src/PERA/PERA_MainWindow.cpp

HEADERS  += \
	src/MessagesWidget.hpp \
	src/DirectoryGuide.hpp \
	src/FileRemover.hpp \
	src/Application.hpp \
	src/MainWindow.hpp \
	src/DirectoryTreeRemover.hpp \
	src/DirectoryTreeRemoverThread.hpp \
	src/Icons.hpp \
	src/MessagesTreeWidget.hpp \
	src/PERA/PERA_AboutDialog.hpp \
	src/PERA/PERA_Application.hpp \
	src/PERA/PERA_MainWindow.hpp

RESOURCES += \
	src/Images.qrc

OTHER_FILES += \
	src/DeleteOldFiles.rc \
    gpl.txt
