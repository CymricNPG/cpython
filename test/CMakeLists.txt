SET( testOutName "TestSuite")

add_executable(${testOutName} TestSuite.cpp)

target_link_libraries(${testOutName} py_module ${PYTHON_LIBRARIES} ${Boost_LIBRARIES}  )
set_target_properties(${testOutName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)
add_test(NAME ${testOutName} COMMAND ${CMAKE_SOURCE_DIR}/bin/${testOutName})

