cmake_minimum_required(VERSION 3.5)
project(EXERCISE08 CXX)


set(treap_src
    treap_bst.h
    treap_bst.txx
    )

set(main_src
    compress.cpp
    )

set(unittest_src
   catch.hpp
   test_treap.cpp
   )

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main ${main_src} ${treap_src})

# create the unit_tests executable
add_executable(unit_tests ${unittest_src} ${treap_src})

enable_testing()
add_test(unit_tests unit_tests)
