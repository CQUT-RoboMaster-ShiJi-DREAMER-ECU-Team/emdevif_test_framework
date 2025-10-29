cmake_minimum_required(VERSION 3.27)

project(emdevif_test_framework C)

option(EMDEVIF_TEST_FRAMEWORK_ENABLE_TEST "Enabled it to enable test for emdevif_test_framework" OFF)

add_library(${PROJECT_NAME} STATIC)

target_include_directories(${PROJECT_NAME} PUBLIC inc/)

target_sources(${PROJECT_NAME} PRIVATE src/emdevif_test_framework.c)

# 将宏 EMDEVIF_TEST_FRAMEWORK_ENABLE_TEST 设置为 ON 即启用测试
if (EMDEVIF_TEST_FRAMEWORK_ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif ()
