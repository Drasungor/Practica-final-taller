cmake_minimum_required(VERSION 3.16)
project(ej_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(ej_3 main.cpp)

target_link_libraries(ej_3 pthread)