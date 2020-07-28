cmake_minimum_required( VERSION 3.12 )
project( DeleteOldFiles )

find_package(Qt5 COMPONENTS REQUIRED Widgets)

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

add_subdirectory(CppAidKit)
include(CppAidKit/cmake/all_options.cmake)

add_executable(DeleteOldFiles
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
set_default_target_options(DeleteOldFiles)
target_link_libraries(DeleteOldFiles AidKit Qt5::Widgets)

