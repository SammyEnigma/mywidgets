
cmake_minimum_required(VERSION 2.9.0)
message(STATUS "cmake build ZCUI")

project(ZCUI)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)
set(CMAKE_AUTOMOC TRUE)

add_definitions(-DCUI_EXPORTS)

set(ZCUI_HEADER
	global.h
	logger.h
	cscrollstyle.h
	popupwidget.h
	switchbutton.h
	singleapplication.h
	)

set(ZCUI_SRC
	logger.cpp
	cscrollstyle.cpp
	popupwidget.cpp
	switchbutton.cpp
	singleapplication.cpp
	)
set(ZCUI_UI
	)
set(ZCUI_QRC
	)
	
qt5_wrap_ui(ZCUI_UI_Headers ${ZCUI_UI})
qt5_add_resources(QRC_Sources ${ZCUI_QRC})

macro(add_target)
	add_library(ZCUI SHARED
		${ZCUI_HEADER}
		${ZCUI_SRC}
		${ZCUI_UI_Headers}
		${QRC_Sources}
		)
endmacro()

add_target()

target_link_libraries(ZCUI
	Qt5::Widgets
	Qt5::Network
	)
