cmake_minimum_required(VERSION 3.28)

project(cpp_test C CXX)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        emdevif_test_framework
        test_function_impl
)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)
