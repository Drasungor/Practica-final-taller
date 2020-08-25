cmake_minimum_required(VERSION 3.16)
project(ej_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(ej_1 main.cpp)

target_link_libraries(ej_1 pthread)