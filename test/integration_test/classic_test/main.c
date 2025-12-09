/**
 * @file main.c
 * @brief 测试框架的测试主函数
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "emdevif_test_framework.h"

#include "test_function_impl.h"
#include "external_test.h"

TEST_SUIT(SuccessTest)
{
    TEST_CASE_BEGIN(a)
    {
        EXPECT_TRUE(1 == 1)->EMDEVIF_TEST_MESSAGE("1 should be equal to 1!");
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

        EMDEVIF_TEST_INT_ASSERT_EQ(1, 1, "");
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(UIntCompare)
    {
        UINT_EXPECT_EQ(3, 3);
        UINT_EXPECT_GT(235326, 45);
        UINT_EXPECT_NE(1, 2);
        UINT_EXPECT_GE(20, 9);
        UINT_EXPECT_GE(2, 2);
        UINT_EXPECT_LT(9, 10);
        UINT_EXPECT_LE(1, 3540);
        UINT_EXPECT_LE(114514, 114514);

        EMDEVIF_TEST_UINT_ASSERT_EQ(1, 1, "");
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(StringEq)
    {
        EXPECT_STREQ("fwsg", "fwsg");

        const char* str1 = "Hfhueiwsgb";
        EXPECT_STREQ("Hfhueiwsgb", str1);
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(FloatPointCompare)
    {
        FP_EXPECT_EQ(3.0, 3.0000001);
        FP_EXPECT_GT(235.326, -4.5);
        FP_EXPECT_NE(1.0, 1.001);
        FP_EXPECT_GE(2.1, 2.0);
        FP_EXPECT_GE(2.0, 2.0);
        FP_EXPECT_LT(-9.1, -9.0);
        FP_EXPECT_LE(-1.0, -0.0);
        FP_EXPECT_LE(-114.514, -114.514);

        EMDEVIF_TEST_FP_ASSERT_EQ(1.0, 1.0, "");
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
        INT_EXPECT_LT(9, 0);
        INT_EXPECT_LT(-9, -9);
        INT_EXPECT_LE(1, 0);

        UINT_EXPECT_EQ(2, 3);
        UINT_EXPECT_GT(1, 45);
        UINT_EXPECT_GT(45, 45);
        UINT_EXPECT_NE(1, 1);
        UINT_EXPECT_GE(2, 9);
        UINT_EXPECT_LT(90, 10);
        UINT_EXPECT_LT(10, 10);
        UINT_EXPECT_LE(17458388, 3540);

        char str_arr[] = "Hello, World!";
        EXPECT_STREQ(str_arr, "dsuighr")->MESSAGE("str_arr is: %s", str_arr);

        FP_EXPECT_EQ(3.0, 3.001);
        FP_EXPECT_GT(-235.326, -4.5);
        FP_EXPECT_NE(1.0, 1.000001);
        FP_EXPECT_GE(-2.1, 2.0);
        FP_EXPECT_LT(-9.1, -9.1);
        FP_EXPECT_LE(1.0, 0.0);
    }
    TEST_CASE_END();
}

TEST_SUIT(AllApiUsageTest)
{
    TEST_CASE_BEGIN(TrueFalse)
    {
        EXPECT_TRUE(true);
        EXPECT_FALSE(false);

        ASSERT_TRUE(true, "");
        ASSERT_FALSE(false, "");
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(Int)
    {
        INT_EXPECT_EQ(1, 1);
        INT_EXPECT_NE(1, -1);
        INT_EXPECT_GT(1, -1);
        INT_EXPECT_LT(-1, 1);
        INT_EXPECT_GE(1, -1);
        INT_EXPECT_LE(-1, -1);

        INT_ASSERT_EQ(1, 1, "");
        INT_ASSERT_NE(1, -1, "");
        INT_ASSERT_GT(1, -1, "");
        INT_ASSERT_LT(-1, 1, "");
        INT_ASSERT_GE(1, -1, "");
        INT_ASSERT_LE(-1, -1, "");
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(UInt)
    {
        UINT_EXPECT_EQ(2, 2);
        UINT_EXPECT_NE(2, 5);
        UINT_EXPECT_GT(6, 5);
        UINT_EXPECT_LT(2, 5);
        UINT_EXPECT_GE(6, 5);
        UINT_EXPECT_LE(2, 5);

        UINT_ASSERT_EQ(2, 2, "");
        UINT_ASSERT_NE(2, 5, "");
        UINT_ASSERT_GT(6, 5, "");
        UINT_ASSERT_LT(2, 5, "");
        UINT_ASSERT_GE(6, 5, "");
        UINT_ASSERT_LE(2, 5, "");
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(String)
    {
        EXPECT_STREQ("asdfghjkl", "asdfghjkl");
        ASSERT_STREQ("asdfghjkl", "asdfghjkl", "");
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(UInt)
    {
        FP_EXPECT_EQ(1.0f, 1.0f);
        FP_EXPECT_NE(1.0f, 3.0f);
        FP_EXPECT_GT(4.0f, 3.0f);
        FP_EXPECT_LT(1.0f, 3.0f);
        FP_EXPECT_GE(4.0f, 3.0f);
        FP_EXPECT_LE(1.0f, 3.0f);

        FP_ASSERT_EQ(1.0f, 1.0f, "");
        FP_ASSERT_NE(1.0f, 3.0f, "");
        FP_ASSERT_GT(4.0f, 3.0f, "");
        FP_ASSERT_LT(1.0f, 3.0f, "");
        FP_ASSERT_GE(4.0f, 3.0f, "");
        FP_ASSERT_LE(1.0f, 3.0f, "");
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
    if (FixtureTest_getA(&fixture_test) != -9631014) {
        printf("FixtureTest failed: a = %d\n", FixtureTest_getA(&fixture_test));
    }
}

static void testFinishHandler(const emdevif_test_ErrorCode error_code)
{
    exit((error_code == EMDEVIF_TEST_EXIST_FAIL ? 0 : 1));
}

int main(void)
{
    openFile();

    const emdevif_test_Callbacks cb = {.printfCallback = my_printf,
                                       .testEntryCallback = testApiUsage,
                                       .testFinishCallback = testFinishHandler};

    emdevif_test_framework_main("\n", &cb, NULL);

    closeFile();

    return 0;
}
