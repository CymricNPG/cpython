SET( testOutName "TestSuite")

file(GLOB_RECURSE cppFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(${testOutName} ${cppFiles})

target_link_libraries(${testOutName} py_module ${PYTHON_LIBRARIES} ${Boost_LIBRARIES}  )
set_target_properties(${testOutName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)
add_test(NAME ${testOutName} COMMAND ${CMAKE_SOURCE_DIR}/bin/${testOutName})

