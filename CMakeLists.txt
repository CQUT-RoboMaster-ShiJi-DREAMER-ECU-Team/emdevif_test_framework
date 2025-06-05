cmake_minimum_required(VERSION 3.5)

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

# 将宏 RMDEV_TEST_FRAMEWORK_ENABLE_TEST 设置为 ON 即启用测试
if (RMDEV_TEST_FRAMEWORK_ENABLE_TEST)
    add_subdirectory(test)
endif ()
