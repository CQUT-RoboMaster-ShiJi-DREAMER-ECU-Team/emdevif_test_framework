/**
 * @file test_function_impl.h
 * @author DuYicheng
 * @date 2025-07-21
 * @brief 测试函数的实现
 */

#pragma once
#ifndef TEST_FUNCTION_IMPL_H
#define TEST_FUNCTION_IMPL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TestFunc {
    FILE* file;
} TestFunc;

static inline void TestFunc_Init(TestFunc* self, const char* name)
{
    self->file = fopen(name, "w");
    if (self->file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(-1);
    }
}

static inline void TestFunc_End(TestFunc* self)
{
    fclose(self->file);
    self->file = NULL;
}

#endif  // !TEST_FUNCTION_IMPL_H
