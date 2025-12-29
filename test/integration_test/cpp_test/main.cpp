/**
 * @file main.cpp
 * @brief 测试框架的测试主函数
 */

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include "emdevif_test_framework.h"

#include "test_function_impl.h"

static TestFunc func;

static void my_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vfprintf(func.file, format, args);

    va_end(args);
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

    TEST_CASE_BEGIN(InLambdaTest)
    {
        [EMDEVIF_TEST_LAMBDA_CAPTURE] {
            EXPECT_TRUE(true);
            EXPECT_FALSE(false);

            ASSERT_TRUE(true, "");
            ASSERT_FALSE(false, "");

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

            EXPECT_STREQ("asdfghjkl", "asdfghjkl");
            ASSERT_STREQ("asdfghjkl", "asdfghjkl", "");

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
        }();
    }
    TEST_CASE_END();
}

TEST_SUIT(TestCaseContextTest)
{
    auto aTestFunc = [](emdevif_test_TestCaseContex* contex) {
        RUN_TEST_CASE_WITHIN_CONTEX_BEGIN(contex)
        {
            INT_EXPECT_EQ(114, 114);
            INT_EXPECT_EQ(514, 514);
            INT_EXPECT_GE(1919, 810);
            EXPECT_TRUE(true);
            EXPECT_STREQ("dfesag", "dfesag");

            FP_EXPECT_EQ(214.623, -14.37);
            INT_EXPECT_EQ(256, -14718)->MESSAGE("expect fail.");
            EXPECT_FALSE(true);
        }
        RUN_TEST_CASE_WITHIN_CONTEX_END();
    };

    TEST_CASE_BEGIN(A)
    {
        EXPECT_TRUE(true);

        emdevif_test_TestCaseContex contex = GET_THIS_TEST_CASE_CONTEXT();
        aTestFunc(&contex);

        EXPECT_FALSE(false);
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(B)
    {
        EXPECT_FALSE(false);

        emdevif_test_TestCaseContex contex = GET_THIS_TEST_CASE_CONTEXT();
        aTestFunc(&contex);

        EXPECT_TRUE(true);
    }
    TEST_CASE_END();
}

static void testEntry()
{
    RUN_SUIT(AllApiUsageTest);
    RUN_SUIT(TestCaseContextTest);
}

static void testFinishHandler(const emdevif_test_ErrorCode error_code)
{
    exit((error_code == EMDEVIF_TEST_EXIST_FAIL ? 0 : 1));
}

int main()
{
    TestFunc_Init(&func, "cpp_test.out");

    constexpr emdevif_test_Callbacks cb{my_printf, testEntry, testFinishHandler, nullptr};

    emdevif_test_framework_main("\n", &cb, nullptr);

    TestFunc_End(&func);

    return 0;
}
