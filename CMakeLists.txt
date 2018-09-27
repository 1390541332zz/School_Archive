cmake_minimum_required(VERSION 3.5)
project(QtHello)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

add_executable(widget_events main.cpp widget_events.hpp widget_events.cpp)
target_link_libraries(widget_events Qt5::Widgets)
