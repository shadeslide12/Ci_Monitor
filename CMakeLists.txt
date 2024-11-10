cmake_minimum_required(VERSION 3.20)
project(Little_Chart)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 5.15 COMPONENTS Core Gui Widgets Charts REQUIRED)

if(Qt5_FOUND)
    message(STATUS "Qt Core Dir:${Qt5Core_DIR}")
endif()

add_executable(Little_Chart 
        main.cpp
        mainwindow.cpp
        mainwindow.h
        MonitorPlot.cpp
        MonitorPlot.h
)

target_link_libraries(Little_Chart 
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
)
