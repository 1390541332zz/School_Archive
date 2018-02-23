cmake_minimum_required(VERSION 3.5)
project(M1 CXX)

# add source for any additional modules here
set(LIB_SOURCE
  token.hpp token.cpp
  lexer.hpp lexer.cpp
  parser.hpp parser.cpp)

# add source for any additional unit tests here
set(TEST_SOURCE
  lexer_test.cpp
  parser_test.cpp)

# add source for simmips program here
set(SIMMIPS_SOURCE simmips.cpp)

#Force Strict Mode
set(STRICT ON)

# You should not need to edit below this line
#-----------------------------------------------------------------------
#-----------------------------------------------------------------------

# try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# optional strict mode
if(UNIX AND STRICT)
  message("-- Enabling strict compilation mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -ggdb -Wall -Wextra -Wpedantic -Werror -Wchkp -Wno-sign-compare -Wno-deprecated")
endif()

# enable Sanatisers
if (SAN)
  message("-- Enabling UBSan and ASan")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address -lubsan -lasan")
endif()

# setup testing
set(TEST_FILE_DIR "${CMAKE_SOURCE_DIR}/tests")
configure_file(${CMAKE_SOURCE_DIR}/test_config.hpp.in 
  ${CMAKE_BINARY_DIR}/test_config.hpp)
include_directories(${CMAKE_BINARY_DIR})

# executables
add_executable(unit_tests catch.hpp unit_tests.cpp ${TEST_SOURCE} ${LIB_SOURCE})
add_executable(simmips ${SIMMIPS_SOURCE} ${LIB_SOURCE})

# Tests
#----------------------------------------------------------------------
enable_testing()

# unit tests
add_test(unit_tests unit_tests)

# M1 functional tests - expected pass
add_test(test_pass_unix_0 simmips ${TEST_FILE_DIR}/pass/unix/test00.asm)
add_test(test_pass_unix_1 simmips ${TEST_FILE_DIR}/pass/unix/test01.asm)
add_test(test_pass_unix_2 simmips ${TEST_FILE_DIR}/pass/unix/test02.asm)
add_test(test_pass_unix_3 simmips ${TEST_FILE_DIR}/pass/unix/test03.asm)
add_test(test_pass_unix_4 simmips ${TEST_FILE_DIR}/pass/unix/test04.asm)
add_test(test_pass_unix_5 simmips ${TEST_FILE_DIR}/pass/unix/test05.asm)
add_test(test_pass_unix_6 simmips ${TEST_FILE_DIR}/pass/unix/test06.asm)
add_test(test_pass_unix_7 simmips ${TEST_FILE_DIR}/pass/unix/test07.asm)
add_test(test_pass_unix_8 simmips ${TEST_FILE_DIR}/pass/unix/test08.asm)
add_test(test_pass_win_0 simmips ${TEST_FILE_DIR}/pass/win/test00.asm)
add_test(test_pass_win_1 simmips ${TEST_FILE_DIR}/pass/win/test01.asm)
add_test(test_pass_win_2 simmips ${TEST_FILE_DIR}/pass/win/test02.asm)
add_test(test_pass_win_3 simmips ${TEST_FILE_DIR}/pass/win/test03.asm)
add_test(test_pass_win_4 simmips ${TEST_FILE_DIR}/pass/win/test04.asm)
add_test(test_pass_win_5 simmips ${TEST_FILE_DIR}/pass/win/test05.asm)
add_test(test_pass_win_6 simmips ${TEST_FILE_DIR}/pass/win/test06.asm)
add_test(test_pass_win_7 simmips ${TEST_FILE_DIR}/pass/win/test07.asm)
add_test(test_pass_win_8 simmips ${TEST_FILE_DIR}/pass/win/test08.asm)

# M1 functional tests - expected fail
add_test(test_fail_unix_0 simmips ${TEST_FILE_DIR}/fail/unix/test00.asm)
add_test(test_fail_unix_1 simmips ${TEST_FILE_DIR}/fail/unix/test01.asm)
add_test(test_fail_unix_2 simmips ${TEST_FILE_DIR}/fail/unix/test02.asm)
add_test(test_fail_unix_3 simmips ${TEST_FILE_DIR}/fail/unix/test03.asm)
add_test(test_fail_unix_4 simmips ${TEST_FILE_DIR}/fail/unix/test04.asm)
add_test(test_fail_unix_5 simmips ${TEST_FILE_DIR}/fail/unix/test05.asm)
add_test(test_fail_unix_6 simmips ${TEST_FILE_DIR}/fail/unix/test06.asm)
add_test(test_fail_unix_7 simmips ${TEST_FILE_DIR}/fail/unix/test07.asm)
add_test(test_fail_win_0 simmips ${TEST_FILE_DIR}/fail/win/test00.asm)
add_test(test_fail_win_1 simmips ${TEST_FILE_DIR}/fail/win/test01.asm)
add_test(test_fail_win_2 simmips ${TEST_FILE_DIR}/fail/win/test02.asm)
add_test(test_fail_win_3 simmips ${TEST_FILE_DIR}/fail/win/test03.asm)
add_test(test_fail_win_4 simmips ${TEST_FILE_DIR}/fail/win/test04.asm)
add_test(test_fail_win_5 simmips ${TEST_FILE_DIR}/fail/win/test05.asm)
add_test(test_fail_win_6 simmips ${TEST_FILE_DIR}/fail/win/test06.asm)
add_test(test_fail_win_7 simmips ${TEST_FILE_DIR}/fail/win/test07.asm)

set_tests_properties(
  test_fail_unix_0
  test_fail_unix_1
  test_fail_unix_2
  test_fail_unix_3
  test_fail_unix_4
  test_fail_unix_5
  test_fail_unix_6
  test_fail_unix_7
  test_fail_win_0
  test_fail_win_1
  test_fail_win_2
  test_fail_win_3
  test_fail_win_4
  test_fail_win_5
  test_fail_win_6
  test_fail_win_7
  PROPERTIES WILL_FAIL ON)

# In the reference environment enable coverage on tests
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
  message("-- Enabling test coverage")
  set(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  set_target_properties(unit_tests PROPERTIES COMPILE_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS} )
  target_link_libraries(unit_tests gcov)
  add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E env "ROOT=${CMAKE_CURRENT_SOURCE_DIR}"
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/coverage.sh)
endif()

# In the reference environment enable memory checking on tests
if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
  message("-- Enabling memory checks")
  add_custom_target(memtest
    COMMAND valgrind ${CMAKE_BINARY_DIR}/unit_tests)
endif()
