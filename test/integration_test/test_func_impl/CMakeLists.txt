cmake_minimum_required(VERSION 3.28)

project(test_function_impl C)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ./)
