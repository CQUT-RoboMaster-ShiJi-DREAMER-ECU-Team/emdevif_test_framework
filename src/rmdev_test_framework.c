/**
 * @file rmdev_test_framework.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief rmdev 测试框架
 */

#include "rmdev_test_framework.h"

#ifndef RMDEV_TEST_DO_NOT_PRINT_PASSED_TEST
#define RMDEV_TEST_DO_NOT_PRINT_PASSED_TEST RMDEV_TEST_FALSE
#endif

enum {
    RMDEV_TEST_NO_ERROR = 0,           ///< 无错误
    RMDEV_TEST_NO_BREAK_CHARACTER,     ///< 没有设置换行符
    RMDEV_TEST_NO_PRINTF_CALLBACK,     ///< 没有设置 printf 回调函数
    RMDEV_TEST_NO_DELAY_CALLBACK,      ///< 没有设置 delay 回调函数
    RMDEV_TEST_NO_TEST_ITEM_CALLBACK,  ///< 没有设置 test_item 回调函数
    RMDEV_TEST_TEST_ITEM_COUNT_ERROR,  ///< 测试项计数与成功、错误的项目计数不匹配
    RMDEV_TEST_OTHER_ERROR             ///< 其他错误
};

unsigned char rmdev_test_error_code = RMDEV_TEST_NO_ERROR;  ///< 测试框架错误码

static const char* break_character;                         ///< 换行符

static rmdev_test_printfCallback printfCallback_ = RMDEV_TEST_NULL;
static rmdev_test_delayCallback delayCallback_ = RMDEV_TEST_NULL;
static rmdev_test_testItemCallback testItemCallback_ = RMDEV_TEST_NULL;

static int test_item_total_count = 0U;                     ///< 测试项计数
static int success_count = 0U;                             ///< 成功计数
static int fail_count = 0U;                                ///< 失败计数

static rmdev_test_bool_t in_test_item = RMDEV_TEST_FALSE;  ///< 是否在测试项中

static const char* current_test_item_name = "";            ///< 当前测试项名称
static int test_item_index = 0U;                           ///< 测试项编号
static int test_item_success_count = 0U;                   ///< 单个测试项成功计数
static int test_item_fail_count = 0U;                      ///< 单个测试项失败计数

static void rmdev_test_finish(void);
static void rmdev_test_item_finish(const char* name);

/// 打印行分割线
#define PRINTF_LINE(void) printfCallback_("==================================================%s", break_character)

/// 打印单行分割线
#define PRINTF_SINGLE_LINE(void) \
    printfCallback_("--------------------------------------------------%s", break_character)

/// 结束的死循环
#define END_LOOP(void) \
    do {               \
    } while (RMDEV_TEST_TRUE)

/**
 * 测试项结束
 * @param name 结束的测试项的名称
 */
static void rmdev_test_item_finish(const char* name)
{
    in_test_item = RMDEV_TEST_FALSE;

    if (test_item_index != test_item_success_count + test_item_fail_count) {
        printfCallback_(
            "rmdev_test_framework Fatal error: Test item count (%d) does not match success (%d) and fail (%d) "
            "counts!%s",
            test_item_index,
            test_item_success_count,
            test_item_fail_count,
            break_character);

        rmdev_test_error_code = RMDEV_TEST_TEST_ITEM_COUNT_ERROR;
        END_LOOP();
    }

    PRINTF_SINGLE_LINE();
    printfCallback_("    Test item \"%s\" finished.%s", name, break_character);
    printfCallback_("    %d test(s) succeeded, %d test(s) failed.%s",
                    test_item_success_count,
                    test_item_fail_count,
                    break_character);
    PRINTF_SINGLE_LINE();
}

void rmdev_test_item(const char* name, const char* file, const int line)
{
    if (!in_test_item) {
        in_test_item = RMDEV_TEST_TRUE;
        test_item_index = 0U;
        test_item_success_count = 0U;
        test_item_fail_count = 0U;
        current_test_item_name = name;

        PRINTF_LINE();
        printfCallback_("    Test item \"%s\" started.%s", name, break_character);
        printfCallback_("    (In file %s:%d)%s", file, line, break_character);
        PRINTF_LINE();
    }
    else {
        rmdev_test_item_finish(current_test_item_name);
        rmdev_test_item(name, file, line);
    }
}

void rmdev_test_check(const char* file, const int line, const rmdev_test_bool_t result)
{
    if (!in_test_item) {
        printfCallback_("Error: Test check called without a test item started!%s", break_character);
        END_LOOP();
    }

    ++test_item_total_count;
    ++test_item_index;

    if (result) {
#if (!RMDEV_TEST_DO_NOT_PRINT_PASSED_TEST)
        printfCallback_("No.%d passed.%s", test_item_index, break_character);
#endif

        ++success_count;
        ++test_item_success_count;
    }
    else {
        printfCallback_("No.%d check failed at %s:%d.%s", test_item_index, file, line, break_character);
        ++fail_count;
        ++test_item_fail_count;
    }
}

void rmdev_test_assert(const char* file, const int line, const rmdev_test_bool_t result)
{
    if (!in_test_item) {
        printfCallback_("Error: Test assert called without a test item started!%s", break_character);
        END_LOOP();
    }

    ++test_item_total_count;
    ++test_item_index;

    if (result) {
#if (!RMDEV_TEST_DO_NOT_PRINT_PASSED_TEST)
        printfCallback_("No.%d passed.%s", test_item_index, break_character);
#endif

        ++success_count;
        ++test_item_success_count;
    }
    else {
        printfCallback_("No.%d assert failed at %s:%d.%s", test_item_index, file, line, break_character);
        ++fail_count;
        ++test_item_fail_count;

        rmdev_test_item_finish(current_test_item_name);
        rmdev_test_finish();
    }
}

/**
 * rmdev 测试框架 结束测试
 */
static void rmdev_test_finish(void)
{
    if (success_count + fail_count == test_item_total_count) {
        printfCallback_("%sTest Finished.%s%s    %d Test(s) Succeeded, %d Test(s) Failed.\r\n",
                        break_character,
                        break_character,
                        break_character,
                        success_count,
                        fail_count);
    }
    else {
        rmdev_test_error_code = RMDEV_TEST_TEST_ITEM_COUNT_ERROR;

        printfCallback_(
            "rmdev_test_framework Fatal error: Test item count (%d) does not match success (%d) and fail (%d) "
            "counts!%s",
            test_item_total_count,
            success_count,
            fail_count,
            break_character);
    }

    END_LOOP();
}

void rmdev_test_framework_main(const char* break_char,
                               const rmdev_test_printfCallback printfCallback,
                               const rmdev_test_delayCallback delayCallback,
                               const rmdev_test_testItemCallback testItemCallback)
{
    break_character = break_char;

    printfCallback_ = printfCallback;
    delayCallback_ = delayCallback;
    testItemCallback_ = testItemCallback;

    if (break_character == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_BREAK_CHARACTER;
        END_LOOP();
    }
    if (printfCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_PRINTF_CALLBACK;
        END_LOOP();
    }
    if (delayCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_DELAY_CALLBACK;
        printfCallback_("rmdev_test_framework Fatal error: No delay callback function set!%s", break_character);
        END_LOOP();
    }
    if (testItemCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_TEST_ITEM_CALLBACK;
        printfCallback_("rmdev_test_framework Fatal error: No test item callback function set!%s", break_character);
        END_LOOP();
    }

    testItemCallback_();

    rmdev_test_item_finish(current_test_item_name);

    rmdev_test_finish();
}
