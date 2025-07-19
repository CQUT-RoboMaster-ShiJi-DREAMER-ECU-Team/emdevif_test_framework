/**
 * @file platform_test_impl.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 平台测试 - 函数的实现
 */

#include "platform_test_impl.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#include "main.h"
#include "usart.h"
#include "rmdev_test_framework.h"

static void serialPrint(const char* buffer, const uint16_t size)
{
    for (uint16_t i = 0; i < size; ++i) {
        while (HAL_UART_GetState(&huart6) != HAL_UART_STATE_READY) {
        }

        while (HAL_UART_Transmit(&huart6, (const uint8_t*)&buffer[i], sizeof(char), HAL_MAX_DELAY) != HAL_OK) {
        }
    }
}

static void testPrintf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    char printf_buffer[500] = {'\0'};

    vsprintf(printf_buffer, format, args);

    serialPrint(printf_buffer, strlen(printf_buffer));

    va_end(args);
}

static void testDelay(const unsigned int ms)
{
    HAL_Delay(ms);
}

static void testItem(void)
{
    RMDEV_TEST_ITEM("Constant Test");
    RMDEV_TEST_EXPECT(true);
    RMDEV_TEST_EXPECT(false);

    RMDEV_TEST_ITEM("Calculate Test");
    RMDEV_TEST_EXPECT((1 + 1) == 2);
    RMDEV_TEST_EXPECT((2 * 2) == 4);
    RMDEV_TEST_EXPECT((3 - 1) == 2);

    RMDEV_TEST_EXPECT((10 / 2) == 5);
    RMDEV_TEST_EXPECT((5 % 2) == 1);
    RMDEV_TEST_EXPECT((7 * 3) == 21);
    RMDEV_TEST_EXPECT((8 - 3) == 5);
    RMDEV_TEST_EXPECT((4 + 6) == 10);

    RMDEV_TEST_EXPECT((10 / 3) == 4);  // false

    RMDEV_TEST_ASSERT((15 / 3) == 5);
    RMDEV_TEST_ASSERT((9 % 3) == 0);
    RMDEV_TEST_ASSERT((6 * 6) == 36);

    RMDEV_TEST_EXPECT((2 * 2) == 5);  // false

    RMDEV_TEST_ASSERT((20 - 10) == 10);
    RMDEV_TEST_ASSERT((3 + 7) == 10);

    RMDEV_TEST_EXPECT((1 + 1) == 3);  // false

    RMDEV_TEST_EXPECT((114514 + 1919810) == 2034324);
    RMDEV_TEST_ASSERT(-1 - 2 == -3);

    RMDEV_TEST_ITEM("None Test");

    RMDEV_TEST_ITEM("Assert Test");
    RMDEV_TEST_ASSERT(true);
    RMDEV_TEST_ASSERT(false);

    RMDEV_TEST_EXPECT(true);
}

/**
 * stm32f407ighx 平台的测试函数入口
 * @note 由于 platform_test 库不是链接到 stm32cubemx 的，所以要在这里再包装一层
 */
void stm32f407ighx_test_main(void)
{
    rmdev_test_framework_main("\n", testPrintf, testDelay, testItem);
}
