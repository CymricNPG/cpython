
file(GLOB_RECURSE cppFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

set(LIB_MODULE "py_module")
add_library(${LIB_MODULE} SHARED ${cppFiles})
set_target_properties(${LIB_MODULE} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

target_link_libraries (${LIB_MODULE} ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})

