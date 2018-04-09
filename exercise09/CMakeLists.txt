cmake_minimum_required(VERSION 3.5)
project(QtHello)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

set(LABEL_SOURCE hello_label.cpp label_printer.cpp)
set(BUTTON_SOURCE hello_button.cpp button_printer.cpp)

add_executable(hello_static hello_static.cpp)
add_executable(hello_label ${LABEL_SOURCE})
add_executable(hello_button ${BUTTON_SOURCE})
target_link_libraries(hello_static Qt5::Widgets)
target_link_libraries(hello_label Qt5::Widgets)
target_link_libraries(hello_button Qt5::Widgets)

