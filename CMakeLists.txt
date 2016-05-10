cmake_minimum_required (VERSION 2.8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror=return-type -Wextra -Wno-unused-parameter -Wpedantic" )

set(PYTHON_VERSION 3.5 CACHE STRING "Python version")

FIND_PACKAGE(PythonLibs ${PYTHON_VERSION} REQUIRED)

find_package(NumPy REQUIRED)
include_directories(${NUMPY_INCLUDE_DIRS})

SET(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
set(BOOST_VERSION 1.60.0)

FIND_PACKAGE(Boost ${BOOST_VERSION} COMPONENTS python filesystem system  timer REQUIRED)

add_definitions(-std=c++11)

ADD_SUBDIRECTORY(src)

SET( app_name "main")

add_executable(${app_name} "src/main.cpp")

target_link_libraries(${app_name}  ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} py_module )

set_target_properties(${app_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR})
