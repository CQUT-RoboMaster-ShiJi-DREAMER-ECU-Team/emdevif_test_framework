/**
 * @file check_bool_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 布尔类型检查宏
 */

#pragma once
#ifndef RMDEV_TEST_CHECK_BOOL_MACRO_H
#define RMDEV_TEST_CHECK_BOOL_MACRO_H

#include "rmdev_test_framework/core.h"

#define RMDEV_TEST_EXPECT_TRUE(result)                  \
    (rmdev___msg.test_suit = rmdev___suit,              \
     rmdev___msg.file = __FILE__,                       \
     rmdev___msg.line = __LINE__,                       \
     rmdev___msg.current_case_name = rmdev___case_name, \
     rmdev___msg.rhs_name = #result,                    \
     rmdev_test_checkTure(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_EXPECT, result))

#define RMDEV_TEST_EXPECT_FALSE(result)                 \
    (rmdev___msg.test_suit = rmdev___suit,              \
     rmdev___msg.file = __FILE__,                       \
     rmdev___msg.line = __LINE__,                       \
     rmdev___msg.current_case_name = rmdev___case_name, \
     rmdev___msg.rhs_name = #result,                    \
     rmdev_test_checkFalse(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_EXPECT, result))

#define RMDEV_TEST_ASSERT_TRUE(result, format, ...)                                     \
    do {                                                                                \
        rmdev___msg.test_suit = rmdev___suit;                                           \
        rmdev___msg.file = __FILE__;                                                    \
        rmdev___msg.line = __LINE__;                                                    \
        rmdev___msg.current_case_name = rmdev___case_name;                              \
        rmdev___msg.rhs_name = #result;                                                 \
        rmdev_test_checkTure(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_ASSERT, result);       \
        if (!rmdev___msg.is_passed) {                                                   \
            rmdev_test___printfCallback___(format, ##__VA_ARGS__);                      \
            rmdev_test___printfCallback___("%s", rmdev_test___line_break_character___); \
            rmdev_test_assertFailEntry();                                               \
        }                                                                               \
    } while (0)

#define RMDEV_TEST_ASSERT_FALSE(result, format, ...)                                    \
    do {                                                                                \
        rmdev___msg.test_suit = rmdev___suit;                                           \
        rmdev___msg.file = __FILE__;                                                    \
        rmdev___msg.line = __LINE__;                                                    \
        rmdev___msg.current_case_name = rmdev___case_name;                              \
        rmdev___msg.rhs_name = #result;                                                 \
        rmdev_test_checkFalse(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_ASSERT, result);      \
        if (!rmdev___msg.is_passed) {                                                   \
            rmdev_test___printfCallback___(format, ##__VA_ARGS__);                      \
            rmdev_test___printfCallback___("%s", rmdev_test___line_break_character___); \
            rmdev_test_assertFailEntry();                                               \
        }                                                                               \
    } while (0)

#endif  // !RMDEV_TEST_CHECK_BOOL_MACRO_H
