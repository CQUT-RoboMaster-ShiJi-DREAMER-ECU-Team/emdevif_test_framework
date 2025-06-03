/**
 * @file rmdev_test_framework.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief rmdev 测试框架
 */

#include "rmdev_test_framework.h"

static int success_count = 0U;  ///< 成功计数
static int fail_count = 0U;     ///< 失败计数

/**
 * rmdev 测试框架 延时函数
 * @attention 这是接口函数，具体实现需要根据平台来编写，即需要在平台的相关文件中实现这个函数的定义。
 * @param ms 毫秒数
 */
void rmdev_test_delay(unsigned int ms);

/**
 * rmdev 测试框架 测试项
 * @attention 这是接口函数，需要在平台的相关文件中实现这个函数的定义。
 */
void rmdev_test_testItem(void);

static void rmdev_test_finish(void);

void rmdev_test_check(const char* name, const char* file, const int line, const rmdev_test_bool_t result)
{
    if (result) {
        rmdev_test_printf("Test %s passed.\r\n", name);
        ++success_count;
    }
    else {
        rmdev_test_printf("Test %s failed at %s:%d.\r\n", name, file, line);
        ++fail_count;
    }
}

void rmdev_test_assert(const char* name, const char* file, const int line, const rmdev_test_bool_t result)
{
    if (result) {
        rmdev_test_printf("Assert %s passed.\r\n", name);
        ++success_count;
    }
    else {
        rmdev_test_printf("Assert %s failed at %s:%d.\r\nTest failed!\r\n", name, file, line);
        ++fail_count;

        rmdev_test_finish();
    }
}

/**
 * rmdev 测试框架 结束测试
 */
static void rmdev_test_finish(void)
{
    rmdev_test_printf("\r\nTest Finished.\r\n\r\n  %d Test(s) Succeeded, %d Test(s) Failed.\r\n",
                      success_count,
                      fail_count);
    while (RMDEV_TEST_TRUE) {
    }
}

void rmdev_test_framework_main(void)
{
    rmdev_test_testItem();

    rmdev_test_finish();
}
