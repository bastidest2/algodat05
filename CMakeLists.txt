cmake_minimum_required(VERSION 3.7.2)
project(algo05)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

include_directories ("${PROJECT_SOURCE_DIR}")
add_executable(algo05 algo05.cpp general_tree.hpp)
