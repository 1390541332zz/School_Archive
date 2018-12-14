cmake_minimum_required(VERSION 3.5)
project(Ex05 CXX)

add_executable(wordcount wordcount.cpp)
set_property(TARGET wordcount PROPERTY CXX_STANDARD 11)
