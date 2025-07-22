/**
 * @file main.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架的测试主函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "rmdev_test_framework-no_prefix.h"

#include "test_function_impl.h"

static TestFunc func;

static void my_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vfprintf(func.file, format, args);

    va_end(args);
}

TEST_SUIT(NoCaseTest) {}

static void testEntry(void)
{
    RUN_SUIT(NoCaseTest);
}

static void testFinishHandler(const rmdev_test_ErrorCode error_code)
{
    exit((error_code == RMDEV_TEST_ALL_PASSED ? 0 : 1));
}

int main(void)
{
    TestFunc_Init(&func, "no_case_test.out");

    const rmdev_test_Callbacks cb = {.printfCallback = my_printf,
                                     .delayCallback = delayImpl,
                                     .testEntryCallback = testEntry,
                                     .testFinishCallback = testFinishHandler};

    rmdev_test_framework_main("\n", &cb, NULL);

    TestFunc_End(&func);

    return 0;
}
