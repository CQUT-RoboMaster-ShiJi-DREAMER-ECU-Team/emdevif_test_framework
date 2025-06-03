/**
 * @file test_function_impl.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架所需要的函数的实现
 */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h> // For sleep function
#include <stdbool.h>

#include "rmdev_test_framework.h"

void rmdev_test_testItem(void)
{
    RMDEV_TEST_CHECK("true", true);
    RMDEV_TEST_CHECK("false", false);

    RMDEV_TEST_CHECK("1 + 1", (1 + 1) == 2);
    RMDEV_TEST_CHECK("2 * 2", (2 * 2) == 4);
    RMDEV_TEST_CHECK("3 - 1", (3 - 1) == 2);

    RMDEV_TEST_CHECK("1 + 1 == 3", (1 + 1) == 3);

    RMDEV_TEST_ASSERT("true 1", true);
    //RMDEV_TEST_ASSERT("false", false);

    RMDEV_TEST_CHECK("true 2", true);
}

void rmdev_test_Delay(const unsigned int ms)
{
    sleep(ms);
}

void rmdev_test_Printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}
