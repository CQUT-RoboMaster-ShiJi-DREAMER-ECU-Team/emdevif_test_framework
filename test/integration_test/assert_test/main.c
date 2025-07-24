/**
 * @file main.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架的测试主函数
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "rmdev_test_framework.h"

#include "test_function_impl.h"

static TestFunc func;

static void my_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vfprintf(func.file, format, args);

    va_end(args);
}

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
}

TEST_SUIT(AssertFailTest)
{
    TEST_CASE_BEGIN(a)
    {
        EXPECT_FALSE(3 != 3);
        EXPECT_TRUE(1);
        ASSERT_TRUE(false, "value = %s", "false");
        ASSERT_TRUE(true, "");
    }
    TEST_CASE_END();
}

TEST_SUIT(TrueTest)
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
    }
    TEST_CASE_END();
}

static void testEntry(void)
{
    RUN_SUIT(SuccessTest);
    RUN_SUIT(AssertFailTest);
    RUN_SUIT(TrueTest);
}

static void testFinishHandler(const rmdev_test_ErrorCode error_code)
{
    exit((error_code == RMDEV_TEST_EXIST_FAIL ? 0 : 1));
}

int main(void)
{
    TestFunc_Init(&func, "assert_test.out");

    const rmdev_test_Callbacks cb = {.printfCallback = my_printf,
                                     .testEntryCallback = testEntry,
                                     .testFinishCallback = testFinishHandler};

    rmdev_test_framework_main("\n", &cb, NULL);

    TestFunc_End(&func);

    return 0;
}
