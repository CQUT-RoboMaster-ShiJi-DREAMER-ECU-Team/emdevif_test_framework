/**
 * @file external_test.c
 * @author DuYicheng
 * @date 2025-07-19
 * @brief 外部文件测试
 */

#include "external_test.h"

#include "emdevif_test_framework-with_prefix.h"

struct FixtureTest {
    emdevif_test_TestFixture fixture;

    int a;
};

static void fixture_setUp(emdevif_test_TestFixture* this_)
{
    FixtureTest* const self = (FixtureTest*)this_;

    self->a = 11235813;
}

static void fixture_tearDown(emdevif_test_TestFixture* this_)
{
    FixtureTest* const self = (FixtureTest*)this_;

    self->a = -9631014;
}

// 仅供验证 tearDown 是否被执行使用
int FixtureTest_getA(const FixtureTest* this_)
{
    return this_->a;
}

FixtureTest fixture_test;

void FixtureTest_Constructor(FixtureTest* this_)
{
    emdevif_test_TestFixture_Constructor(this_, fixture_setUp, fixture_tearDown);
}

EMDEVIF_TEST_TEST_SUIT(FixtureTest)
{
    EMDEVIF_TEST_TEST_CASE_BEGIN(CheckSetUp)
    {
        EMDEVIF_TEST_EXPECT_TRUE(fixture_test.a == 11235813)
            ->EMDEVIF_TEST_MESSAGE("fixture_test.a should be 11235813, but got %d!", fixture_test.a);
    }
    EMDEVIF_TEST_TEST_CASE_END();
}

EMDEVIF_TEST_TEST_SUIT(ExternalTest)
{
    EMDEVIF_TEST_TEST_CASE_BEGIN(ExternalTestCase)
    {
        EMDEVIF_TEST_EXPECT_TRUE(1 == 1);
        EMDEVIF_TEST_EXPECT_FALSE(114514 == 1919810);
        EMDEVIF_TEST_EXPECT_FALSE(67978 == 0)->EMDEVIF_TEST_MESSAGE("67978 should not be equal to 0!");
    }
    EMDEVIF_TEST_TEST_CASE_END();

    EMDEVIF_TEST_TEST_CASE_BEGIN(ExternalTestCase)
    {
        EMDEVIF_TEST_EXPECT_TRUE(1 == 1)->EMDEVIF_TEST_MESSAGE("1 should be equal to 1!");
        EMDEVIF_TEST_EXPECT_FALSE(114514 != 1919810);
        EMDEVIF_TEST_EXPECT_FALSE(67978 != 0)->EMDEVIF_TEST_MESSAGE("67978 should not be equal to 0!");
    }
    EMDEVIF_TEST_TEST_CASE_END();
}
