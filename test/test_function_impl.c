/**
 * @file test_function_impl.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架所需要的函数的实现
 */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h> // For sleep function

void my_delay(const unsigned int ms)
{
    sleep(ms);
}

void my_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}
