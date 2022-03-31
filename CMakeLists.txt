cmake_minimum_required(VERSION 3.20)
project(univ2_OOP_lab1)

add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(univ2.2_OOP_lab1 main.cpp Graph.h Geometry.h)