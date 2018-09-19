cmake_minimum_required(VERSION 3.8)
project(C)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/andrey/CLionProjects/shad/hw3/C/bin")
set(SOURCE_FILES src/main.cpp)

add_executable(C ${SOURCE_FILES})