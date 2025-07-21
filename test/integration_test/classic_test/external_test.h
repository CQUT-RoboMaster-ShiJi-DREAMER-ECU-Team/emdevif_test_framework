/**
 * @file external_test.h
 * @author DuYicheng
 * @date 2025-07-19
 * @brief 外部文件测试
 */

#pragma once
#ifndef EXTERNAL_TEST_H
#define EXTERNAL_TEST_H

#include "rmdev_test_framework.h"

typedef struct FixtureTest {
    rmdev_test_TestFixture fixture;

    int a;
} FixtureTest;

extern FixtureTest fixture_test;

extern void FixtureTest_Constructor(FixtureTest* this_);

extern RMDEV_TEST_TEST_SUIT(ExternalTest);
extern RMDEV_TEST_TEST_SUIT(FixtureTest);

#endif  // !EXTERNAL_TEST_H
