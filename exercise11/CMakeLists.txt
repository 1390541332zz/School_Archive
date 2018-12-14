cmake_minimum_required(VERSION 3.5)
project(Ex11 CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

add_executable(ex11 main.cpp complex_widget.hpp complex_widget.cpp)
set(TARGET ex11 PROPERTY CXX_STANDARD 11)
target_link_libraries(ex11 Qt5::Widgets)
