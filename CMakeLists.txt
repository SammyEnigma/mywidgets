
cmake_minimum_required(VERSION 2.9.0)
message(STATUS "cmake build Example")

project(Example)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_AUTOMOC TRUE)

set(ZCUI_DIR "${CMAKE_SOURCE_DIR}/ZCUI")
include_directories("${ZCUI_DIR}")

set(EXAMPLE_HEADER
	widget.h
	)

set(EXAMPLE_SRC
	main.cpp
	widget.cpp
	)
set(EXAMPLE_UI
	widget.ui
	)
set(EXAMPLE_QRC
	)
	
qt5_wrap_ui(EXAMPLE_UI_Headers ${EXAMPLE_UI})
qt5_add_resources(QRC_Sources ${EXAMPLE_QRC})

add_subdirectory (ZCUI)

add_executable(Example WIN32
	${EXAMPLE_HEADER}
	${EXAMPLE_SRC}
	${EXAMPLE_UI_Headers}
	${QRC_Sources}
	)

target_link_libraries(Example
	ZCUI
	Qt5::Widgets
	)
