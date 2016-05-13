cmake_minimum_required (VERSION 2.8)

# General C++11

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror=return-type -Wextra -Wno-unused-parameter -Wpedantic" )
add_definitions(-std=c++11)

# Use libasan

option(WITH_ASAN "build application with clang asan" OFF)

if(WITH_ASAN)
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -g3 -fno-omit-frame-pointer -fsanitize=address" )
    SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}  -fsanitize=address" )
endif(WITH_ASAN)

# Python

set(PYTHON_VERSION 3.5 CACHE STRING "Python version")
FIND_PACKAGE(PythonLibs ${PYTHON_VERSION} REQUIRED)
include_directories (${PYTHON_INCLUDE_DIRS})

# BOOST

SET(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(BOOST_VERSION 1.60.0)
FIND_PACKAGE(Boost ${BOOST_VERSION} COMPONENTS python filesystem system  timer unit_test_framework REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
