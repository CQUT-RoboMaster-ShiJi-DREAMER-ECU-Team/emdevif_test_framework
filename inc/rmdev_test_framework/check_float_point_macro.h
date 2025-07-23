/**
 * @file check_float_point_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 检查 int 类型的宏
 */

#pragma once
#ifndef CHECK_FLOAT_POINT_MACRO_H
#define CHECK_FLOAT_POINT_MACRO_H

#include "rmdev_test_framework/core.h"
#include "rmdev_test_framework/compare_auxiliary_macro.h"

#define RMDEV_TEST_FP_EXPECT_EQ(lhs, rhs)     \
    (RMDEV_TEST__COMPARE_SET_VALUE(lhs, rhs), \
     rmdev_test_floatPointCompare(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_EXPECT, RMDEV_TEST_COMPARE_EQUAL, lhs, rhs))

#define RMDEV_TEST_FP_EXPECT_NE(lhs, rhs)     \
    (RMDEV_TEST__COMPARE_SET_VALUE(lhs, rhs), \
     rmdev_test_floatPointCompare(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_EXPECT, RMDEV_TEST_COMPARE_NOT_EQUAL, lhs, rhs))

#define RMDEV_TEST_FP_EXPECT_GT(lhs, rhs)                          \
    (RMDEV_TEST__COMPARE_SET_VALUE(lhs, rhs),                      \
     rmdev_test_floatPointCompare(&rmdev___msg,                    \
                                  RMDEV_TEST_CHECK_TYPE_EXPECT,    \
                                  RMDEV_TEST_COMPARE_GREATER_THAN, \
                                  lhs,                             \
                                  rhs))

#define RMDEV_TEST_FP_EXPECT_LT(lhs, rhs)     \
    (RMDEV_TEST__COMPARE_SET_VALUE(lhs, rhs), \
     rmdev_test_floatPointCompare(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_EXPECT, RMDEV_TEST_COMPARE_LESS_THAN, lhs, rhs))

#define RMDEV_TEST_FP_EXPECT_GE(lhs, rhs)                           \
    (RMDEV_TEST__COMPARE_SET_VALUE(lhs, rhs),                       \
     rmdev_test_floatPointCompare(&rmdev___msg,                     \
                                  RMDEV_TEST_CHECK_TYPE_EXPECT,     \
                                  RMDEV_TEST_COMPARE_GREATER_EQUAL, \
                                  lhs,                              \
                                  rhs))

#define RMDEV_TEST_FP_EXPECT_LE(lhs, rhs)                        \
    (RMDEV_TEST__COMPARE_SET_VALUE(lhs, rhs),                    \
     rmdev_test_floatPointCompare(&rmdev___msg,                  \
                                  RMDEV_TEST_CHECK_TYPE_EXPECT,  \
                                  RMDEV_TEST_COMPARE_LESS_EQUAL, \
                                  lhs,                           \
                                  rhs))

// ===========================================================================

#define RMDEV_TEST_FP_ASSERT_EQ(lhs, rhs, format, ...)         \
    do {                                                       \
        RMDEV_TEST_FP_EXPECT_EQ(lhs, rhs);                     \
        RMDEV_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define RMDEV_TEST_FP_ASSERT_NE(lhs, rhs, format, ...)         \
    do {                                                       \
        RMDEV_TEST_FP_EXPECT_NE(lhs, rhs);                     \
        RMDEV_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define RMDEV_TEST_FP_ASSERT_GT(lhs, rhs, format, ...)         \
    do {                                                       \
        RMDEV_TEST_FP_EXPECT_GT(lhs, rhs);                     \
        RMDEV_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define RMDEV_TEST_FP_ASSERT_LT(lhs, rhs, format, ...)         \
    do {                                                       \
        RMDEV_TEST_FP_EXPECT_LT(lhs, rhs);                     \
        RMDEV_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define RMDEV_TEST_FP_ASSERT_GE(lhs, rhs, format, ...)         \
    do {                                                       \
        RMDEV_TEST_FP_EXPECT_GE(lhs, rhs);                     \
        RMDEV_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#define RMDEV_TEST_FP_ASSERT_LE(lhs, rhs, format, ...)         \
    do {                                                       \
        RMDEV_TEST_FP_EXPECT_LE(lhs, rhs);                     \
        RMDEV_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#endif  // !CHECK_FLOAT_POINT_MACRO_H
