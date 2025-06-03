cmake_minimum_required(VERSION 3.28)

project(rmdev_test_framework C)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        inc/
)

file(GLOB_RECURSE RMDEV_TEST_FRAMEWORK_PUBLIC_SOURCES "src/*.c")
target_sources(${PROJECT_NAME}
    INTERFACE
        ${RMDEV_TEST_FRAMEWORK_PUBLIC_SOURCES}
)

if (RMDEV_TEST_FRAMEWORK_ENABLE_TEST)
    add_subdirectory(test)
endif ()
