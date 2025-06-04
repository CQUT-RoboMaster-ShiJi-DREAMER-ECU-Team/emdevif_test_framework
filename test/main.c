/**
 * @file main.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架的测试主函数
 */

#include "rmdev_test_framework.h"

#include <stdbool.h>

#include "test_function_impl.h"

void testUsage(void)
{
    RMDEV_TEST_ITEM("Constant Test");
    RMDEV_TEST_CHECK(true);
    RMDEV_TEST_CHECK(false);

    RMDEV_TEST_ITEM("Calculate Test");
    RMDEV_TEST_CHECK((1 + 1) == 2);
    RMDEV_TEST_CHECK((2 * 2) == 4);
    RMDEV_TEST_CHECK((3 - 1) == 2);

    RMDEV_TEST_CHECK((10 / 2) == 5);
    RMDEV_TEST_CHECK((5 % 2) == 1);
    RMDEV_TEST_CHECK((7 * 3) == 21);
    RMDEV_TEST_CHECK((8 - 3) == 5);
    RMDEV_TEST_CHECK((4 + 6) == 10);

    RMDEV_TEST_CHECK((10 / 3) == 4);  // false

    RMDEV_TEST_ASSERT((15 / 3) == 5);
    RMDEV_TEST_ASSERT((9 % 3) == 0);
    RMDEV_TEST_ASSERT((6 * 6) == 36);

    RMDEV_TEST_CHECK((2 * 2) == 5);  // false

    RMDEV_TEST_ASSERT((20 - 10) == 10);
    RMDEV_TEST_ASSERT((3 + 7) == 10);

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
    // todo 待增加其他的测试（比如传入空指针）
    rmdev_test_framework_main("\n", my_printf, my_delay, testUsage);

    return 0;
}
