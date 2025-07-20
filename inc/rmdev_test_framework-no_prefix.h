/**
 * @file rmdev_test_framework-no_prefix.h
 * @author DuYicheng
 * @date 2025-07-19
 * @brief 不带前缀的 rmdev 测试框架头文件
 */

#pragma once
#ifndef RMDEV_TEST_FRAMEWORK_NO_PREFIX_H
#define RMDEV_TEST_FRAMEWORK_NO_PREFIX_H

#include "rmdev_test_framework.h"

#define TEST_SUIT       RMDEV_TEST_TEST_SUIT

#define TEST_CASE_BEGIN RMDEV_TEST_TEST_CASE_BEGIN
#define TEST_CASE_END   RMDEV_TEST_TEST_CASE_END

#define RUN_SUIT        RMDEV_TEST_RUN_SUIT
#define RUN_SUIT_F      RMDEV_TEST_RUN_SUIT_F

#define EXPECT_TRUE     RMDEV_TEST_EXPECT_TRUE
#define EXPECT_FALSE    RMDEV_TEST_EXPECT_FALSE
#define ASSERT_TRUE     RMDEV_TEST_ASSERT_TRUE
#define ASSERT_FALSE    RMDEV_TEST_ASSERT_FALSE

#define MESSAGE         RMDEV_TEST_MESSAGE

#endif  // !RMDEV_TEST_FRAMEWORK_NO_PREFIX_H
