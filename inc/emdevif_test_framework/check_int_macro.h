/**
 * @file check_int_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 检查 int 类型的宏
 */

#pragma once
#ifndef EMDEVIF_TEST_CHECK_INT_MACRO_H
#define EMDEVIF_TEST_CHECK_INT_MACRO_H

#include "emdevif_test_framework/core.h"
#include "emdevif_test_framework/compare_auxiliary_macro.h"

#define EMDEVIF_TEST_INT_EXPECT_EQ(lhs, rhs)                         \
    (EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs),                      \
     emdevif_test_intCompare(&emdevif_current_test_compare_message_, \
                             EMDEVIF_TEST_CHECK_TYPE_EXPECT,         \
                             EMDEVIF_TEST_COMPARE_EQUAL,             \
                             lhs,                                    \
                             rhs))

#define EMDEVIF_TEST_INT_EXPECT_NE(lhs, rhs)                         \
    (EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs),                      \
     emdevif_test_intCompare(&emdevif_current_test_compare_message_, \
                             EMDEVIF_TEST_CHECK_TYPE_EXPECT,         \
                             EMDEVIF_TEST_COMPARE_NOT_EQUAL,         \
                             lhs,                                    \
                             rhs))

#define EMDEVIF_TEST_INT_EXPECT_GT(lhs, rhs)                         \
    (EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs),                      \
     emdevif_test_intCompare(&emdevif_current_test_compare_message_, \
                             EMDEVIF_TEST_CHECK_TYPE_EXPECT,         \
                             EMDEVIF_TEST_COMPARE_GREATER_THAN,      \
                             lhs,                                    \
                             rhs))

#define EMDEVIF_TEST_INT_EXPECT_LT(lhs, rhs)                         \
    (EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs),                      \
     emdevif_test_intCompare(&emdevif_current_test_compare_message_, \
                             EMDEVIF_TEST_CHECK_TYPE_EXPECT,         \
                             EMDEVIF_TEST_COMPARE_LESS_THAN,         \
                             lhs,                                    \
                             rhs))

#define EMDEVIF_TEST_INT_EXPECT_GE(lhs, rhs)                         \
    (EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs),                      \
     emdevif_test_intCompare(&emdevif_current_test_compare_message_, \
                             EMDEVIF_TEST_CHECK_TYPE_EXPECT,         \
                             EMDEVIF_TEST_COMPARE_GREATER_EQUAL,     \
                             lhs,                                    \
                             rhs))

#define EMDEVIF_TEST_INT_EXPECT_LE(lhs, rhs)                         \
    (EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs),                      \
     emdevif_test_intCompare(&emdevif_current_test_compare_message_, \
                             EMDEVIF_TEST_CHECK_TYPE_EXPECT,         \
                             EMDEVIF_TEST_COMPARE_LESS_EQUAL,        \
                             lhs,                                    \
                             rhs))

// ===========================================================================

#define EMDEVIF_TEST_INT_ASSERT_EQ(lhs, rhs, format, ...)        \
    do {                                                         \
        EMDEVIF_TEST_INT_EXPECT_EQ(lhs, rhs);                    \
        EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define EMDEVIF_TEST_INT_ASSERT_NE(lhs, rhs, format, ...)        \
    do {                                                         \
        EMDEVIF_TEST_INT_EXPECT_NE(lhs, rhs);                    \
        EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define EMDEVIF_TEST_INT_ASSERT_GT(lhs, rhs, format, ...)        \
    do {                                                         \
        EMDEVIF_TEST_INT_EXPECT_GT(lhs, rhs);                    \
        EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define EMDEVIF_TEST_INT_ASSERT_LT(lhs, rhs, format, ...)        \
    do {                                                         \
        EMDEVIF_TEST_INT_EXPECT_LT(lhs, rhs);                    \
        EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define EMDEVIF_TEST_INT_ASSERT_GE(lhs, rhs, format, ...)        \
    do {                                                         \
        EMDEVIF_TEST_INT_EXPECT_GE(lhs, rhs);                    \
        EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define EMDEVIF_TEST_INT_ASSERT_LE(lhs, rhs, format, ...)        \
    do {                                                         \
        EMDEVIF_TEST_INT_EXPECT_LE(lhs, rhs);                    \
        EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#endif  // !EMDEVIF_TEST_CHECK_INT_MACRO_H
