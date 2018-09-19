cmake_minimum_required(VERSION 3.8)
project(A)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(SOURCE_FILES main.cpp)
add_executable(A ${SOURCE_FILES})