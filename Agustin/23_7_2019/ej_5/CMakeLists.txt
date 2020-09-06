cmake_minimum_required(VERSION 3.16)
project(ej_5)

find_package(Qt5 REQUIRED Widgets Core)
#include_directories(${Qt5_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(ej_5 main.cpp)

add_compile_options(ej_5 -fPIE)

#target_link_options(ej_5)