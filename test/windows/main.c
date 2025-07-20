/**
 * @file main.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief 测试框架的测试主函数
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rmdev_test_framework-no_prefix.h"

#include "test_function_impl.h"
#include "external_test.h"

TEST_SUIT(SuccessTest)
{
    TEST_CASE_BEGIN(a)
    {
        EXPECT_TRUE(1 == 1)->RMDEV_TEST_MESSAGE("1 should be equal to 1!");
        EXPECT_FALSE(114514 == 1919810);
        EXPECT_FALSE(67978 == 0);
        ASSERT_TRUE(1 == 1, "1 should be equal to 1!");
        ASSERT_TRUE(2 != 1, "");
    }
    TEST_CASE_END();
}

TEST_SUIT(TrueFalseTest)
{
    TEST_CASE_BEGIN(ExpectSuccess)
    {
        EXPECT_TRUE(true);
        EXPECT_FALSE(false);
    }
    TEST_CASE_END();

    TEST_CASE_BEGIN(ExpectFail)
    {
        EXPECT_TRUE(1 == 3)->MESSAGE("1 should not be equal to %d!", 3);
        EXPECT_FALSE(114514 == 114514)->MESSAGE("114514 should not be equal to 114514!");
    }
    TEST_CASE_END();
}

void testApiUsage(void)
{
    RUN_SUIT(SuccessTest);
    RUN_SUIT(TrueFalseTest);
    RUN_SUIT(ExternalTest);

    FixtureTest_Constructor(&fixture_test);
    RUN_SUIT_F(FixtureTest, &fixture_test);
    if (fixture_test.a != -9631014) {
        printf("FixtureTest failed: a = %d\n", fixture_test.a);
    }
}

void testFinishHandler(void)
{
    exit(0);
}

int main(const int argc, char* argv[])
{
    int choice = 1;

    if (argc == 2) {
        char* end_ptr;
        choice = strtol(argv[1], &end_ptr, 10);

        if (*end_ptr != '\0' || choice < 1 || choice > 5) {
            fprintf(stderr, "Invalid argument! Please provide a number between 1 and 5.\n");
            return -1;
        }
    }
    else if (argc == 1) {
        // do nothing
    }
    else {
        fprintf(stderr, "Invalid argument! Please provide a number between 1 and 5.\n");
        return -1;
    }

    const rmdev_test_Callbacks cb = {.printfCallback = my_printf,
                                     .delayCallback = my_delay,
                                     .testEntryCallback = testApiUsage,
                                     .testFinishCallback = testFinishHandler};

    switch (choice) {
    case 1:
        rmdev_test_framework_main("\n", &cb);
        break;
    case 2:
        rmdev_test_framework_main(NULL, &cb);
        break;
    case 3:
        rmdev_test_framework_main("\n", &cb);
        break;
    case 4:
        rmdev_test_framework_main("\n", &cb);
        break;
    case 5:
        rmdev_test_framework_main("\n", &cb);
        break;
    default:
        fprintf(stderr, "Invalid choice!\n");
        return -1;
    }

    return 0;
}
