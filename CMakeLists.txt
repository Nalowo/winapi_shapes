cmake_minimum_required(VERSION 3.27.1)

project(winapi_shaps CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(winapi_shaps src/main.cpp
                    src/shapes.cpp
                    src/printer.cpp
                    src/win_printer.cpp)