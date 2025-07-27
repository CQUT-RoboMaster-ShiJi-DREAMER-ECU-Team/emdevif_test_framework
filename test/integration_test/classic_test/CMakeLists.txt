cmake_minimum_required(VERSION 3.28)

project(classic_test C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        emdevif_test_framework
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ./
)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.c
        external_test.c
        test_function_impl.c
)
