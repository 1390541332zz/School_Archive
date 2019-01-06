cmake_minimum_required(VERSION 3.2)
project(myDisassembler)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(  DEFINED ENV{PERSONAL_DEV_ENV}
  OR UNIX
  )
  message("-- Enabling strict compilation mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wpedantic -Werror -Wchkp -Wno-sign-compare -Wno-deprecated")
endif()

add_executable(myDisassembler main.cpp parse_obj.cpp export_disasm.cpp)
