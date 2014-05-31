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

SOURCES += main.cpp\
	MessagesWidget.cpp \
	DirectoryGuide.cpp \
	FileRemover.cpp \
	Application.cpp \
	MainWindow.cpp \
	DirectoryTreeRemover.cpp \
	DirectoryTreeRemoverThread.cpp \
	Icons.cpp \
	MessagesTreeWidget.cpp \
	PERA/PERA_AboutDialog.cpp \
	PERA/PERA_Application.cpp \
	PERA/PERA_MainWindow.cpp

HEADERS  += \
	MessagesWidget.hpp \
	DirectoryGuide.hpp \
	FileRemover.hpp \
	Application.hpp \
	MainWindow.hpp \
	DirectoryTreeRemover.hpp \
	DirectoryTreeRemoverThread.hpp \
	Icons.hpp \
	MessagesTreeWidget.hpp \
	PERA/PERA_AboutDialog.hpp \
	PERA/PERA_Application.hpp \
	PERA/PERA_MainWindow.hpp

RESOURCES += \
	Images.qrc

OTHER_FILES += \
	DeleteOldFiles.rc \
    ../gpl.txt
