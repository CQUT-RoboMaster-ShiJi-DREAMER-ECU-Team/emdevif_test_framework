/**
 * @file check_str_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 检测字符串的宏
 */

#pragma once
#ifndef RMDEV_TEST_CHECK_STR_MACRO_H
#define RMDEV_TEST_CHECK_STR_MACRO_H

#include "rmdev_test_framework/core.h"
#include "rmdev_test_framework/compare_auxiliary_macro.h"

#define RMDEV_TEST_EXPECT_STREQ(lhs, rhs) \
    (RMDEV_TEST__COMPARE_SET_VALUE(lhs, rhs), rmdev_test_strEqual(&rmdev___msg, RMDEV_TEST_CHECK_TYPE_EXPECT, lhs, rhs))

#define RMDEV_TEST_ASSERT_STREQ(lhs, rhs, format, ...)         \
    do {                                                       \
        RMDEV_TEST_EXPECT_STREQ(lhs, rhs);                     \
        RMDEV_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#endif  // !RMDEV_TEST_CHECK_STR_MACRO_H
