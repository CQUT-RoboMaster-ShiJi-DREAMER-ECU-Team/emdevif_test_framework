cmake_minimum_required(VERSION 3.28)

project(emdevif_test_framework_test)

set(EMDEVIF_TEST_FRAMEWORK_TEST_NAME "" CACHE STRING "Select which test to run.")

if (NOT (EMDEVIF_TEST_FRAMEWORK_TEST_NAME STREQUAL ""))
    if (EMDEVIF_TEST_FRAMEWORK_TEST_NAME STREQUAL "integration_test")
        add_subdirectory(integration_test)
    else ()
        message(WARNING "Unsupported platform for test of emdevif_test_framework: ${EMDEVIF_TEST_FRAMEWORK_TEST_NAME}. Skipping.")
    endif ()
else ()
    message(WARNING "EMDEVIF_TEST_FRAMEWORK_TEST_NAME is not defined, so test of emdevif_test_framework skipped. Please set it to a valid platform (e.g., integration_test).")
endif ()
