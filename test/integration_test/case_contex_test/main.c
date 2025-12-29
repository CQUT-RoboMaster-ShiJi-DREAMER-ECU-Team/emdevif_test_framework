/**
 * @file main.c
 * @brief 测试框架的测试主函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

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

static void aTestFunc(emdevif_test_TestCaseContex* contex)
{
    RUN_TEST_CASE_WITHIN_CONTEX_BEGIN(contex)
    {
        INT_EXPECT_EQ(114, 114);
        INT_EXPECT_EQ(514, 514);
        INT_EXPECT_GE(1919, 810);

        FP_EXPECT_EQ(214.623, -14.37);
        INT_EXPECT_EQ(256, -14718)->MESSAGE("expect fail.");
    }
    RUN_TEST_CASE_WITHIN_CONTEX_END();
}

TEST_SUIT(CaseContextTest)
{
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

static void testEntry(void)
{
    RUN_SUIT(CaseContextTest);
}

static void testFinishHandler(const emdevif_test_ErrorCode error_code)
{
    exit((error_code == EMDEVIF_TEST_EXIST_FAIL ? 0 : 1));
}

int main(void)
{
    TestFunc_Init(&func, "case_contex_test.out");

    const emdevif_test_Callbacks cb = {.printfCallback = my_printf,
                                       .testEntryCallback = testEntry,
                                       .testFinishCallback = testFinishHandler};

    emdevif_test_framework_main("\n", &cb, NULL);

    TestFunc_End(&func);

    return 0;
}
