cmake_minimum_required(VERSION 3.5)
project(Treap CXX)

# try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE compress.cpp)

set(TEST test_treap.cpp)

add_executable(treap_test ${TEST})

enable_testing()
add_test(treap_test treap_test)
