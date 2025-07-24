/**
 * @file test_function_impl.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架所需要的函数的实现
 */

#include "test_function_impl.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static FILE* file = NULL;

void my_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    vfprintf(file, format, args);

    va_end(args);
}

void openFile(void)
{
    file = fopen("classic_test.out", "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }
}

void closeFile(void)
{
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}
