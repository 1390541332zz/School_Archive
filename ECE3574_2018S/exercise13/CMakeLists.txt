cmake_minimum_required(VERSION 3.5)
project(SEx14 CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

add_executable(trafficlight main.cpp traffic_light.h traffic_light.cpp)
set_property(TARGET trafficlight PROPERTY CXX_STANDARD 11)
target_link_libraries(trafficlight Qt5::Widgets)
