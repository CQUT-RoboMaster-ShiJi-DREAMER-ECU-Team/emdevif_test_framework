/**
 * @file check_str_macro.h
 * @author DuYicheng
 * @date 2025-07-22
 * @brief 检测字符串的宏
 */

#pragma once
#ifndef EMDEVIF_TEST_CHECK_STR_MACRO_H
#define EMDEVIF_TEST_CHECK_STR_MACRO_H

#include "emdevif_test_framework/core.h"
#include "emdevif_test_framework/compare_auxiliary_macro.h"

#define EMDEVIF_TEST_EXPECT_STREQ(lhs, rhs)     \
    (EMDEVIF_TEST__COMPARE_SET_VALUE(lhs, rhs), \
     emdevif_test_strEqual(&emdevif_current_test_compare_message_, EMDEVIF_TEST_CHECK_TYPE_EXPECT, lhs, rhs))

#define EMDEVIF_TEST_ASSERT_STREQ(lhs, rhs, format, ...)         \
    do {                                                         \
        EMDEVIF_TEST_EXPECT_STREQ(lhs, rhs);                     \
        EMDEVIF_TEST__ASSERT_FAIL_PROCESS(format, ##__VA_ARGS__) \
    } while (0)

#endif  // !EMDEVIF_TEST_CHECK_STR_MACRO_H
