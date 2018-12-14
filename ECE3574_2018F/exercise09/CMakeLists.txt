cmake_minimum_required(VERSION 3.5)
project(QtHello)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

add_executable(hello_static hello_static.cpp)
target_link_libraries(hello_static Qt5::Widgets)
add_executable(hello_label hello_label.cpp label_printer.cpp)
target_link_libraries(hello_label Qt5::Widgets)
