/**
 * @file external_test.h
 * @brief 外部文件测试
 */

#pragma once
#ifndef EXTERNAL_TEST_H
#define EXTERNAL_TEST_H

#include "emdevif_test_framework-with_prefix.h"

typedef struct FixtureTest FixtureTest;

extern FixtureTest fixture_test;

void FixtureTest_Constructor(FixtureTest* this_);
int FixtureTest_getA(const FixtureTest* this_);

EMDEVIF_TEST_TEST_SUIT(ExternalTest);
EMDEVIF_TEST_TEST_SUIT(FixtureTest);

#endif  // !EXTERNAL_TEST_H
