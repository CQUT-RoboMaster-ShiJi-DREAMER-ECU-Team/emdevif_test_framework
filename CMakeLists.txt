cmake_minimum_required(VERSION 3.27)

project(rmdev_test_framework C)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        inc/
)

target_sources(${PROJECT_NAME}
    INTERFACE
        src/rmdev_test_framework.c
)

# 将宏 RMDEV_TEST_FRAMEWORK_ENABLE_TEST 设置为 ON 即启用测试
if (RMDEV_TEST_FRAMEWORK_ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif ()
