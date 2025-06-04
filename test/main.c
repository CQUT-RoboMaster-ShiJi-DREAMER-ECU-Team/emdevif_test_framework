/**
 * @file main.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架的测试主函数
 */

#include "rmdev_test_framework.h"

#include <stdbool.h>

#include "test_function_impl.h"

void my_testItem(void)
{
    RMDEV_TEST_ITEM("Constant Test");
    RMDEV_TEST_CHECK(true);
    RMDEV_TEST_CHECK(false);

    RMDEV_TEST_ITEM("Calculate Test");
    RMDEV_TEST_CHECK((1 + 1) == 2);
    RMDEV_TEST_CHECK((2 * 2) == 4);
    RMDEV_TEST_CHECK((3 - 1) == 2);

    RMDEV_TEST_CHECK((1 + 1) == 3);  // false

    RMDEV_TEST_CHECK((114514 + 1919810) == 2034324);
    RMDEV_TEST_ASSERT(-1 - 2 == -3);

    RMDEV_TEST_ITEM("Assert Test");
    RMDEV_TEST_ASSERT(true);
    RMDEV_TEST_ASSERT(false);

    RMDEV_TEST_CHECK(true);
}

int main(void)
{
    rmdev_test_framework_main("\n", my_printf, my_delay, my_testItem);

    return 0;
}
