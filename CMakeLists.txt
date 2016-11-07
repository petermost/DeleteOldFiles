cmake_minimum_required( VERSION 3.0 )
project( DeleteOldFiles )

include( ../CppAidKit/cmake/all_options.cmake )
include( ../CppAidKit/cmake/aidkit_options.cmake )

set( SOURCES
	src/main.cpp
	src/Application.cpp
	src/DirectoryTreeRemover.cpp
	src/DirectoryTreeRemoverThread.cpp
	src/FileRemover.cpp
	src/Icons.cpp
	src/MainWindow.cpp
	src/MessagesTreeWidget.cpp
)

set( HEADERS
	src/Application.hpp
	src/DirectoryTreeRemover.hpp
	src/DirectoryTreeRemoverThread.hpp
	src/FileRemover.hpp
	src/Icons.hpp
	src/MainWindow.hpp
	src/MessagesTreeWidget.hpp
)

find_package( Qt5Widgets )

qt5_wrap_cpp( MOC_SOURCES ${HEADERS} )

qt5_add_resources( RESOURCES
	src/Images.qrc
)

add_executable( DeleteOldFiles ${SOURCES} ${MOC_SOURCES} ${RESOURCES})

# Qt5 Setup:

#set( CMAKE_AUTOMOC ON )
#find_package( Qt5Widgets )

target_link_libraries( DeleteOldFiles AidKit Qt5::Widgets )

