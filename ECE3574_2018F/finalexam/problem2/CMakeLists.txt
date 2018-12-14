cmake_minimum_required(VERSION 3.5)
project(P2 CXX)

# try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()
  
# require a C++11 compiler and use it for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# build executable
add_executable(P2 main.cpp)
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
  target_link_libraries(P2 pthread)
endif()

