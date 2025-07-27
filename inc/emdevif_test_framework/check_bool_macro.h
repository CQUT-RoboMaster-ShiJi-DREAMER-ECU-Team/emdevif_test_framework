/**
 * @file check_bool_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 布尔类型检查宏
 */

#pragma once
#ifndef EMDEVIF_TEST_CHECK_BOOL_MACRO_H
#define EMDEVIF_TEST_CHECK_BOOL_MACRO_H

#include "emdevif_test_framework/core.h"

#define EMDEVIF_TEST_EXPECT_TRUE(result)                    \
    (emdevif___msg.test_suit = emdevif___suit,              \
     emdevif___msg.file = __FILE__,                         \
     emdevif___msg.line = __LINE__,                         \
     emdevif___msg.current_case_name = emdevif___case_name, \
     emdevif___msg.rhs_name = #result,                      \
     emdevif_test_checkTure(&emdevif___msg, EMDEVIF_TEST_CHECK_TYPE_EXPECT, result))

#define EMDEVIF_TEST_EXPECT_FALSE(result)                   \
    (emdevif___msg.test_suit = emdevif___suit,              \
     emdevif___msg.file = __FILE__,                         \
     emdevif___msg.line = __LINE__,                         \
     emdevif___msg.current_case_name = emdevif___case_name, \
     emdevif___msg.rhs_name = #result,                      \
     emdevif_test_checkFalse(&emdevif___msg, EMDEVIF_TEST_CHECK_TYPE_EXPECT, result))

#define EMDEVIF_TEST_ASSERT_TRUE(result, format, ...)                                       \
    do {                                                                                    \
        emdevif___msg.test_suit = emdevif___suit;                                           \
        emdevif___msg.file = __FILE__;                                                      \
        emdevif___msg.line = __LINE__;                                                      \
        emdevif___msg.current_case_name = emdevif___case_name;                              \
        emdevif___msg.rhs_name = #result;                                                   \
        emdevif_test_checkTure(&emdevif___msg, EMDEVIF_TEST_CHECK_TYPE_ASSERT, result);     \
        if (!emdevif___msg.is_passed) {                                                     \
            emdevif_test___printfCallback___(format, ##__VA_ARGS__);                        \
            emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___); \
            emdevif_test_assertFailEntry();                                                 \
        }                                                                                   \
    } while (0)

#define EMDEVIF_TEST_ASSERT_FALSE(result, format, ...)                                      \
    do {                                                                                    \
        emdevif___msg.test_suit = emdevif___suit;                                           \
        emdevif___msg.file = __FILE__;                                                      \
        emdevif___msg.line = __LINE__;                                                      \
        emdevif___msg.current_case_name = emdevif___case_name;                              \
        emdevif___msg.rhs_name = #result;                                                   \
        emdevif_test_checkFalse(&emdevif___msg, EMDEVIF_TEST_CHECK_TYPE_ASSERT, result);    \
        if (!emdevif___msg.is_passed) {                                                     \
            emdevif_test___printfCallback___(format, ##__VA_ARGS__);                        \
            emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___); \
            emdevif_test_assertFailEntry();                                                 \
        }                                                                                   \
    } while (0)

#endif  // !EMDEVIF_TEST_CHECK_BOOL_MACRO_H
