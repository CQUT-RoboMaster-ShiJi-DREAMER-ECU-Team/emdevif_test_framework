/**
 * @file external_test.c
 * @author DuYicheng
 * @date 2025-07-19
 * @brief 外部文件测试
 */

#include "external_test.h"

#include "rmdev_test_framework.h"

static void fixture_setUp(rmdev_test_TestFixture* this_)
{
    FixtureTest* const self = (FixtureTest*)this_;

    self->a = 11235813;
}

static void fixture_tearDown(rmdev_test_TestFixture* this_)
{
    FixtureTest* const self = (FixtureTest*)this_;

    self->a = -9631014;
}

FixtureTest fixture_test;

void FixtureTest_Constructor(FixtureTest* this_)
{
    this_->fixture.setUp = fixture_setUp;
    this_->fixture.tearDown = fixture_tearDown;
}

RMDEV_TEST_TEST_SUIT(FixtureTest)
{
    RMDEV_TEST_TEST_CASE_BEGIN(CheckSetUp)
    {
        RMDEV_TEST_EXPECT_TRUE(fixture_test.a == 11235813);
    }
    RMDEV_TEST_TEST_CASE_END();
}

RMDEV_TEST_TEST_SUIT(ExternalTest)
{
    RMDEV_TEST_TEST_CASE_BEGIN(ExternalTestCase)
    {
        RMDEV_TEST_EXPECT_TRUE(1 == 1);
        RMDEV_TEST_EXPECT_FALSE(114514 == 1919810);
        RMDEV_TEST_EXPECT_FALSE(67978 == 0);
    }
    RMDEV_TEST_TEST_CASE_END();
}
