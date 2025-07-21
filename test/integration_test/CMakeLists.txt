cmake_minimum_required(VERSION 3.28)

project(integration_test C)

set(CMAKE_C_STANDARD 11)

find_package(Python3 REQUIRED)

add_subdirectory(test_func_impl)

function(runTest test_name)
    add_subdirectory(${test_name})

    add_test(NAME ${test_name}_gen COMMAND ${test_name})
    set_tests_properties(${test_name}_gen PROPERTIES TIMEOUT 3)

    add_test(NAME ${test_name}_process COMMAND
        ${Python3_EXECUTABLE} ${CMAKE_CURRENT_LIST_DIR}/clear_file_line.py ${test_name}
    )

    add_test(NAME ${test_name}_cmp COMMAND
        ${CMAKE_COMMAND}
        -E
        compare_files
        ${test_name}.out
        ${CMAKE_CURRENT_LIST_DIR}/${test_name}.expected
    )

    set_tests_properties(${test_name}_process PROPERTIES DEPENDS ${test_name}_gen)
    set_tests_properties(${test_name}_cmp PROPERTIES DEPENDS ${test_name}_process)
endfunction()

runTest(classic_test)
runTest(assert_test)
