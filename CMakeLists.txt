cmake_minimum_required (VERSION 2.8)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror=return-type -Wextra -Wno-unused-parameter -Wpedantic" )

set(PYTHON_VERSION 2.7 CACHE STRING "Python version")

FIND_PACKAGE(PythonLibs ${PYTHON_VERSION} REQUIRED)

SET(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(BOOST_VERSION 1.60.0)

FIND_PACKAGE(Boost ${BOOST_VERSION} COMPONENTS python filesystem system  timer REQUIRED)

add_definitions(-std=c++11)

ADD_SUBDIRECTORY(src)
