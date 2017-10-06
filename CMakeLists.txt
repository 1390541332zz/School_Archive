cmake_minimum_required(VERSION 3.5)
project(ToggleTestExample CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

add_executable(toggleapp main.cpp toggle_widget.h toggle_widget.cpp)
target_link_libraries(toggleapp Qt5::Widgets)

add_executable(toggletest test_toggle_widget.cpp toggle_widget.h toggle_widget.cpp)
target_link_libraries(toggletest Qt5::Widgets Qt5::Test)

enable_testing()
add_test(toggletest toggletest)
