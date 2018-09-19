cmake_minimum_required(VERSION 3.8)
project(B)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Werror")

set(SOURCE_FILES main.cpp)
add_executable(B ${SOURCE_FILES})