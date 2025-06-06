/**
 * @file main.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架的测试主函数
 */

#include <stdbool.h>
#include <stdio.h>

#include "rmdev_test_framework.h"
#include "test_function_impl.h"

void testApiUsage(void)
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

    RMDEV_TEST_ITEM("None Test");

    RMDEV_TEST_ITEM("Assert Test");
    RMDEV_TEST_ASSERT(true);
    RMDEV_TEST_ASSERT(false);

    RMDEV_TEST_CHECK(true);
}

int main(void)
{
    printf("1 -- Api Usage Test\n");
    printf("2 -- NULL Break Character Test\n");
    printf("3 -- NULL Printf Callback Test\n");
    printf("4 -- NULL Delay Callback Test\n");
    printf("5 -- NULL Test Item Callback Test\n");
    printf("Choose which to test: ");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        rmdev_test_framework_main("\n", my_printf, my_delay, testApiUsage);
        break;
    case 2:
        rmdev_test_framework_main(NULL, my_printf, my_delay, testApiUsage);
        break;
    case 3:
        rmdev_test_framework_main("\n", NULL, my_delay, testApiUsage);
        break;
    case 4:
        rmdev_test_framework_main("\n", my_printf, NULL, testApiUsage);
        break;
    case 5:
        rmdev_test_framework_main("\n", my_printf, my_delay, NULL);
        break;
    default:
        printf("Invalid choice!\n");
        return 1;
    }

    return 0;
}
