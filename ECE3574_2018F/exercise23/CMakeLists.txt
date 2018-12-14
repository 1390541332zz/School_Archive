cmake_minimum_required(VERSION 3.5)
project(Ex23 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_vector catch.hpp test_vector.cpp vector.hpp)

