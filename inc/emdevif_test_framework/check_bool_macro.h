/**
 * @file check_bool_macro.h
 * @brief 布尔类型检查宏
 */

#pragma once
#ifndef EMDEVIF_TEST_CHECK_BOOL_MACRO_H
#define EMDEVIF_TEST_CHECK_BOOL_MACRO_H

#include "emdevif_test_framework/core.h"

#define EMDEVIF_TEST_EXPECT_TRUE(result)                                            \
    (emdevif_current_test_compare_message_.test_suit = &emdevif_current_test_suit_, \
     emdevif_current_test_compare_message_.file = __FILE__,                         \
     emdevif_current_test_compare_message_.line = __LINE__,                         \
     emdevif_current_test_compare_message_.current_case_name = emdevif___case_name, \
     emdevif_current_test_compare_message_.rhs_name = #result,                      \
     emdevif_test_checkTure(&emdevif_current_test_compare_message_, EMDEVIF_TEST_CHECK_TYPE_EXPECT, result))

#define EMDEVIF_TEST_EXPECT_FALSE(result)                                           \
    (emdevif_current_test_compare_message_.test_suit = &emdevif_current_test_suit_, \
     emdevif_current_test_compare_message_.file = __FILE__,                         \
     emdevif_current_test_compare_message_.line = __LINE__,                         \
     emdevif_current_test_compare_message_.current_case_name = emdevif___case_name, \
     emdevif_current_test_compare_message_.rhs_name = #result,                      \
     emdevif_test_checkFalse(&emdevif_current_test_compare_message_, EMDEVIF_TEST_CHECK_TYPE_EXPECT, result))

#define EMDEVIF_TEST_ASSERT_TRUE(result, format, ...)                                                           \
    do {                                                                                                        \
        emdevif_current_test_compare_message_.test_suit = &emdevif_current_test_suit_;                          \
        emdevif_current_test_compare_message_.file = __FILE__;                                                  \
        emdevif_current_test_compare_message_.line = __LINE__;                                                  \
        emdevif_current_test_compare_message_.current_case_name = emdevif___case_name;                          \
        emdevif_current_test_compare_message_.rhs_name = #result;                                               \
        emdevif_test_checkTure(&emdevif_current_test_compare_message_, EMDEVIF_TEST_CHECK_TYPE_ASSERT, result); \
        if (!emdevif_current_test_compare_message_.is_passed) {                                                 \
            emdevif_test___printfCallback___(format, ##__VA_ARGS__);                                            \
            emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___);                     \
            emdevif_test_assertFailEntry();                                                                     \
        }                                                                                                       \
    } while (0)

#define EMDEVIF_TEST_ASSERT_FALSE(result, format, ...)                                                           \
    do {                                                                                                         \
        emdevif_current_test_compare_message_.test_suit = &emdevif_current_test_suit_;                           \
        emdevif_current_test_compare_message_.file = __FILE__;                                                   \
        emdevif_current_test_compare_message_.line = __LINE__;                                                   \
        emdevif_current_test_compare_message_.current_case_name = emdevif___case_name;                           \
        emdevif_current_test_compare_message_.rhs_name = #result;                                                \
        emdevif_test_checkFalse(&emdevif_current_test_compare_message_, EMDEVIF_TEST_CHECK_TYPE_ASSERT, result); \
        if (!emdevif_current_test_compare_message_.is_passed) {                                                  \
            emdevif_test___printfCallback___(format, ##__VA_ARGS__);                                             \
            emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___);                      \
            emdevif_test_assertFailEntry();                                                                      \
        }                                                                                                        \
    } while (0)

#endif  // !EMDEVIF_TEST_CHECK_BOOL_MACRO_H
