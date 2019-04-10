cmake_minimum_required( VERSION 3.12 )
project( DeleteOldFiles )

add_subdirectory( CppAidKit )

include( CppAidKit/cmake/all_options.cmake )

set( SOURCES
	src/main.cpp
	src/Application.hpp
	src/Application.cpp
	src/DirectoryTreeRemover.hpp
	src/DirectoryTreeRemover.cpp
	src/DirectoryTreeRemoverThread.hpp
	src/DirectoryTreeRemoverThread.cpp
	src/FileRemover.hpp
	src/FileRemover.cpp
	src/Icons.hpp
	src/Icons.cpp
	src/MainWindow.hpp
	src/MainWindow.cpp
	src/MessagesTreeWidget.hpp
	src/MessagesTreeWidget.cpp

	src/Images.qrc
)

find_package( Qt5 COMPONENTS REQUIRED Widgets )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

add_executable( DeleteOldFiles ${SOURCES})
target_link_libraries( DeleteOldFiles AidKit Qt5::Widgets )

