cmake_minimum_required( VERSION 3.12 )
project( DeleteOldFiles )

find_package(Qt5 COMPONENTS REQUIRED Widgets)

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

add_subdirectory(CppAidKit)
include(CppAidKit/cmake/AidKit.cmake)

add_googletest_subdirectory()

# 'DeleteOldFiles' executable:

add_executable(DeleteOldFiles
	src/main.cpp
)
set_default_target_options(DeleteOldFiles)
target_link_libraries(DeleteOldFiles
	DeleteOldFilesLib
)

# 'DeleteOldFiles' tests:

add_executable(DeleteOldFilesTests
	tests/SettingsTest.cpp
	tests/IconsTest.cpp
)
set_default_target_options(DeleteOldFilesTests)
target_link_libraries(DeleteOldFilesTests
	DeleteOldFilesLib
	AidKitTest
)

# 'DeleteOldFiles' static lib:

add_library(DeleteOldFilesLib STATIC
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
	src/Settings.hpp
	src/Settings.cpp

	src/Images.qrc
)
set_default_target_options(DeleteOldFilesLib)
target_include_directories(DeleteOldFilesLib
	PUBLIC
		src/
)

target_link_libraries(DeleteOldFilesLib
	AidKit
	Qt5::Widgets
)
