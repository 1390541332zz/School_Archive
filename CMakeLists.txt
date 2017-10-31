cmake_minimum_required(VERSION 3.5)
project(Exercise21 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED Core)
  
ADD_EXECUTABLE(write_file write_file.cpp)
TARGET_LINK_LIBRARIES(write_file Qt5::Core)

ADD_EXECUTABLE(read_file read_file.cpp)
TARGET_LINK_LIBRARIES(read_file Qt5::Core)
