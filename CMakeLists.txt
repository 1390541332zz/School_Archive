if(DEFINED ENV{PERSONAL_DEV_ENV}) 
    cmake_minimum_required(VERSION 3.6)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
else()
    cmake_minimum_required(VERSION 3.5)
endif()

project(PLOTSCRIPT CXX)

set(CMAKE_MODULE_PATH 
    ${CMAKE_MODULE_PATH} 
    "${PROJECT_SOURCE_DIR}/cmake_modules"
   )

set(STARTUP_FILE ${CMAKE_SOURCE_DIR}/startup.pls)
configure_file(${CMAKE_SOURCE_DIR}/startup_config.hpp.in ${CMAKE_BINARY_DIR}/startup_config.hpp)
include_directories(${CMAKE_BINARY_DIR})

set(interpreter_src
  token.cpp
  atom.cpp
  environment.cpp
  expression.cpp
  parse.cpp
  interpreter.cpp   
  )

set(interpreter_h
   token.hpp       
   atom.hpp       
   environment.hpp
   env_helper.hpp 
   env_list.hpp   
   env_arithmetic.hpp
   env_functional.hpp
   expression.hpp 
   parse.hpp      
   interpreter.hpp
   )

set(unittest_src
   atom_tests.cpp
   environment_tests.cpp
   expression_tests.cpp
   interpreter_tests.cpp
   parse_tests.cpp
   semantic_error.hpp
   token_tests.cpp
   unit_tests.cpp
   )

set(tui_src
  )

set(gui_src
   notebook_app.cpp 
   input_widget.cpp 
   output_widget.cpp
   )

set(gui_h
   notebook_app.hpp
   input_widget.hpp
   output_widget.hpp
   )

set(gui_test_h
    qtests/testHelpers.hpp
    qtests/testUI.hpp
    qtests/testPrimitiveGraphics.hpp
    qtests/testDiscretePlotLayout.hpp
    qtests/testContinuousPlotLayout.hpp
   )

set(gui_test_src 
    notebook_test.cpp
   )

set(tui_main
  plotscript.cpp
)

set(gui_main
  notebook.cpp
)

set(clangtidy_srcs 
   ${interpreter_src}
   ${tui_src}
   ${gui_src}
   ${tui_main}
   ${gui_main}
   )
set(all_srcs
   ${interpreter_src}
   ${interpreter_h}
   ${unittest_src}
   ${tui_src}
   ${gui_src}
   ${gui_h}
   ${gui_test_src}
   ${gui_test_h}
   ${tui_main}
   ${gui_main}
   )

# remove hicpp-explicit-conversions later
SET(CLANG_TIDY_CHECKS
      -checks=
      -*,
      bugprone-*,
      cert-*,
      cppcoreguidelines-*,
     -cppcoreguidelines-pro-type-union-access,
     -cppcoreguidelines-pro-bounds-pointer-arithmetic,
     -cppcoreguidelines-pro-bounds-array-to-pointer-decay,
     clang-analyzer-*,
      hicpp-*,
     -hicpp-explicit-conversions,
     -hicpp-no-array-decay,
      misc-*,
     -misc-definitions-in-headers,
      modernize-*,
     -modernize-pass-by-value,
      performance-*,
      portability-*,
      readability-*,
     -readability-named-parameter
   )


# try to prevent accidental in-source builds, these cause lots of problems
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Remove any files created thus far and use a different directory for the build.")
endif()

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# configure Qt
find_package(Qt5 COMPONENTS Widgets Test QUIET)
if (Qt5Widgets_FOUND AND Qt5Test_FOUND)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# optional strict mode
if(UNIX AND CMAKE_COMPILER_IS_GNUCXX)
  message("-- Enabling strict compilation mode")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wpedantic -Werror -Wchkp -Wno-sign-compare -Wno-deprecated")
endif()

# build interpreter library
add_library(interpreter ${interpreter_src})

# create the plotscript executable
add_executable(plotscript ${tui_main} ${tui_src})
target_link_libraries(plotscript interpreter)

# create the unit_tests executable
add_executable(unit_tests catch.hpp ${unittest_src})
target_link_libraries(unit_tests interpreter)

enable_testing()
add_test(unit_tests unit_tests)

# In the reference environment enable coverage on tests
if(  DEFINED ENV{ECE3574_REFERENCE_ENV} 
  OR DEFINED ENV{PERSONAL_DEV_ENV} 
  OR UNIX
  )
  message("-- Enabling test coverage")
  set(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  set_target_properties(interpreter PROPERTIES COMPILE_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS} )
  set_target_properties(unit_tests PROPERTIES COMPILE_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS} )
  target_link_libraries(unit_tests interpreter pthread gcov)
  target_link_libraries(plotscript interpreter pthread gcov)
  add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E env "ROOT=${CMAKE_CURRENT_SOURCE_DIR}"
    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/coverage.sh)
endif()

# In the reference environment enable memory checking on tests
if(  DEFINED ENV{ECE3574_REFERENCE_ENV} 
  OR DEFINED ENV{PERSONAL_DEV_ENV} 
  OR UNIX
  )
  message("-- Enabling memory checks")
  add_custom_target(memtest
    COMMAND valgrind ${CMAKE_BINARY_DIR}/unit_tests)
endif()

# In the reference environment enable tui tests
if(DEFINED ENV{ECE3574_REFERENCE_ENV})
  add_test(plotscript_test python3 ${CMAKE_SOURCE_DIR}/scripts/integration_test.py)
endif()

# -----------------------------------------------------------------------------
# Build the notebook executable and tests if Qt is available
# -----------------------------------------------------------------------------

if (Qt5Widgets_FOUND AND Qt5Test_FOUND)
  
add_executable(notebook ${gui_main} ${gui_src})
  if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(notebook interpreter Qt5::Widgets pthread gcov)
  else(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(notebook interpreter Qt5::Widgets)
  endif()

  add_executable(notebook_test ${gui_test_src} ${gui_src})
  if(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(notebook_test interpreter Qt5::Widgets Qt5::Test pthread gcov)
  else(UNIX AND NOT APPLE AND CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(notebook_test interpreter Qt5::Widgets Qt5::Test)
  endif()

  add_test(notebook_test notebook_test)
  
else (Qt5Widgets_FOUND AND Qt5Test_FOUND)
  message("Qt >= 5.9  needs to be installed to build the notebook interface and related tests.")
endif (Qt5Widgets_FOUND AND Qt5Test_FOUND)


# -----------------------------------------------------------------------------
# Build the Documentation if possible
# -----------------------------------------------------------------------------
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# -----------------------------------------------------------------------------
# Run Clang Format if installed and enabled
# -----------------------------------------------------------------------------

if(DEFINED ENV{PERSONAL_DEV_ENV})
    message("-- Enabling clang-format")
  include(clang-format)
  set(clangformat_srcs ${all_srcs})
  clangformat_setup("${clangformat_srcs}")
endif()

# -----------------------------------------------------------------------------
# Run Clang Tidy if installed and enabled
# -----------------------------------------------------------------------------

if(DEFINED ENV{PERSONAL_DEV_ENV} AND DEFINED ENV{PERSONAL_DEV_ENV_CTIDY})
    message("-- Enabling clang-tidy")
    find_program(
      CLANG_TIDY_EXE
      NAMES "clang-tidy"
      DOC "Path to clang-tidy executable"
      )
    if(NOT CLANG_TIDY_EXE)
      message(STATUS "clang-tidy not found.")
    endif()
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        foreach(clangtidy_src ${clangtidy_srcs})
            get_filename_component(clangtidy_src ${clangtidy_src} ABSOLUTE)
            list(APPEND clangtidy_srcs_tmp ${clangtidy_src})
        endforeach()
        set(clangtidy_srcs "${clangtidy_srcs_tmp}")
        unset(clangtidy_srcs_tmp)
        string(CONCAT clangtidy_opts ${CLANG_TIDY_CHECKS})
        add_custom_target(clangtidy
            COMMAND ${CLANG_TIDY_EXE}
            ${clangtidy_srcs}
            ${clangtidy_opts}
            "-header-filter=${CMAKE_SOURCE_DIR}/*.h*"
            -p ${CMAKE_BINARY_DIR}
        )
    endif()
endif()
