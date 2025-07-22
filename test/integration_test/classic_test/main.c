/**
 * @file main.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架的测试主函数
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rmdev_test_framework-no_prefix.h"

#include "test_function_impl.h"
#include "external_test.h"

TEST_SUIT(SuccessTest)
{
    TEST_CASE_BEGIN(a)
    {
        EXPECT_TRUE(1 == 1)->RMDEV_TEST_MESSAGE("1 should be equal to 1!");
        EXPECT_FALSE(114514 == 1919810);
        EXPECT_FALSE(67978 == 0);
        ASSERT_TRUE(1 == 1, "1 should be equal to 1!");
        ASSERT_TRUE(2 != 1, "");
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(IntCompare)
    {
        INT_EXPECT_EQ(3, 3);
        INT_EXPECT_GT(235326, -45);
        INT_EXPECT_NE(1, 2);
        INT_EXPECT_GE(2, -9);
        INT_EXPECT_GE(2, 2);
        INT_EXPECT_LT(-9, 0);
        INT_EXPECT_LE(-1, 0);
        INT_EXPECT_LE(-114514, -114514);

        RMDEV_TEST_INT_ASSERT_EQ(1, 1, "");
    }
    TEST_CASE_END();
}

TEST_SUIT(TrueFalseTest)
{
    TEST_CASE_BEGIN(ExpectSuccess)
    {
        EXPECT_TRUE(true);
        EXPECT_FALSE(false);
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(ExpectFail)
    {
        EXPECT_TRUE(1 == 3)->MESSAGE("1 should not be equal to %d!", 3);
        EXPECT_FALSE(114514 == 114514)->MESSAGE("114514 should not be equal to 114514!");

        const int a = 3, b = 1;
        INT_EXPECT_EQ(a, b)->MESSAGE("lhs = %d, rhs = %d", a, b);

        INT_EXPECT_EQ(3, -3);
        INT_EXPECT_GT(-235326, -45);
        INT_EXPECT_GT(-235326, -235326);
        INT_EXPECT_NE(2, 2);
        INT_EXPECT_GE(2, 9);
        INT_EXPECT_LT(-9, 0);
        INT_EXPECT_LT(-9, -9);
        INT_EXPECT_LE(1, 0);
    }
    TEST_CASE_END();
}

void testApiUsage(void)
{
    RUN_SUIT(SuccessTest);
    RUN_SUIT(TrueFalseTest);
    RUN_SUIT(ExternalTest);

    FixtureTest_Constructor(&fixture_test);
    RUN_SUIT_F(FixtureTest, &fixture_test);
    if (fixture_test.a != -9631014) {
        printf("FixtureTest failed: a = %d\n", fixture_test.a);
    }
}

static void testFinishHandler(const rmdev_test_ErrorCode error_code)
{
    exit((error_code == RMDEV_TEST_EXIST_FAIL ? 0 : 1));
}

int main(void)
{
    openFile();

    const rmdev_test_Callbacks cb = {.printfCallback = my_printf,
                                     .delayCallback = my_delay,
                                     .testEntryCallback = testApiUsage,
                                     .testFinishCallback = testFinishHandler};

    rmdev_test_framework_main("\n", &cb, NULL);

    closeFile();

    return 0;
}
