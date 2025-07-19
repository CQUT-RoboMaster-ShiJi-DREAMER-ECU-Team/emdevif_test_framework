/**
 * @file rmdev_test_framework.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief rmdev 测试框架
 */

#include "rmdev_test_framework.h"

enum {
    RMDEV_TEST_NO_ERROR = 0,           ///< 无错误
    RMDEV_TEST_NO_BREAK_CHARACTER,     ///< 没有设置换行符
    RMDEV_TEST_NO_PRINTF_CALLBACK,     ///< 没有设置 printf 回调函数
    RMDEV_TEST_NO_DELAY_CALLBACK,      ///< 没有设置 delay 回调函数
    RMDEV_TEST_NO_TEST_SUIT_CALLBACK,  ///< 没有设置 test_suit 回调函数
    RMDEV_TEST_TEST_SUIT_COUNT_ERROR,  ///< 测试项计数与成功、错误的项目计数不匹配
    RMDEV_TEST_OTHER_ERROR             ///< 其他错误
};

unsigned char rmdev_test_error_code = RMDEV_TEST_NO_ERROR;  ///< 测试框架错误码

static const char* line_break_character;                    ///< 换行符

static rmdev_test_printfCallback printfCallback_ = RMDEV_TEST_NULL;
static rmdev_test_delayCallback delayCallback_ = RMDEV_TEST_NULL;
static rmdev_test_testEntryCallback testEntryCallback_ = RMDEV_TEST_NULL;

static const rmdev_test_TestSuit* current_running_suit = RMDEV_TEST_NULL;

static int test_suit_total_count = 0U;    ///< 测试套件计数
static int test_suit_success_count = 0U;  ///< 成功计数
static int test_suit_fail_count = 0U;     ///< 失败计数

static void rmdev_test_finish(void);
static void rmdev_test_expect(rmdev_test_TestSuit* test_suit,
                              const rmdev_test_CompareMsg* msg,
                              rmdev_test_bool_t result);
static void rmdev_test_assert(rmdev_test_TestSuit* test_suit,
                              const rmdev_test_CompareMsg* msg,
                              rmdev_test_bool_t result);

/// 结束的死循环
#define END_LOOP(void) \
    do {               \
    } while (RMDEV_TEST_TRUE)

void rmdev_test_TestFixture_Constructor(void* const this_,
                                        void (*setUp)(rmdev_test_TestFixture* this_),
                                        void (*tearDown)(rmdev_test_TestFixture* this_))
{
    rmdev_test_TestFixture* const self = (rmdev_test_TestFixture*)this_;

    if (self != RMDEV_TEST_NULL) {
        self->setUp = setUp;
        self->tearDown = tearDown;
    }
}

void rmdev_test_expectTure(rmdev_test_TestSuit* const test_suit,
                           rmdev_test_CompareMsg* const msg,
                           const rmdev_test_CheckType check_type,
                           const rmdev_test_bool_t result)
{
    msg->compare_type_msg = "true";
    msg->lhs_name = "expected";
    msg->lhs_value = "true";
    msg->rhs_value = result ? "true" : "false";

    if (check_type == RMDEV_TEST_CHECK_TYPE_EXPECT) {
        rmdev_test_expect(test_suit, msg, result);
    }
    else {
        rmdev_test_assert(test_suit, msg, result);
    }
}

void rmdev_test_expectFalse(rmdev_test_TestSuit* const test_suit,
                            rmdev_test_CompareMsg* const msg,
                            const rmdev_test_CheckType check_type,
                            const rmdev_test_bool_t result)
{
    msg->compare_type_msg = "true";
    msg->lhs_name = "expected";
    msg->lhs_value = "false";
    msg->rhs_value = result ? "true" : "false";

    if (check_type == RMDEV_TEST_CHECK_TYPE_EXPECT) {
        rmdev_test_expect(test_suit, msg, !result);
    }
    else {
        rmdev_test_assert(test_suit, msg, !result);
    }
}

static void rmdev_test_expect(rmdev_test_TestSuit* const test_suit,
                              const rmdev_test_CompareMsg* const msg,
                              const rmdev_test_bool_t result)
{
    ++test_suit->total_count;

    if (result) {
        ++test_suit->success_count;
        printfCallback_(".");
    }
    else {
        ++test_suit->fail_count;

        printfCallback_("F%s", line_break_character);
        printfCallback_("Test suit \"%s\" expect %s: \"%s\" failed at ",
                        test_suit->name,
                        msg->compare_type_msg,
                        msg->current_case_name);
        printfCallback_("%s:%d: %s", msg->file, msg->line, line_break_character);
        printfCallback_("lhs: %s%s    %s%s", msg->lhs_name, line_break_character, msg->lhs_value, line_break_character);
        printfCallback_("rhs: %s%s    %s%s", msg->rhs_name, line_break_character, msg->rhs_value, line_break_character);
    }
}

static void rmdev_test_assert(rmdev_test_TestSuit* const test_suit,
                              const rmdev_test_CompareMsg* const msg,
                              const rmdev_test_bool_t result)
{
    ++test_suit->total_count;

    if (result) {
        ++test_suit->success_count;
        printfCallback_(".");
    }
    else {
        ++test_suit->fail_count;

        printfCallback_("F%s", line_break_character);
        printfCallback_("Test suit \"%s\" assert %s failed at %s:%d:%s",
                        test_suit->name,
                        msg->compare_type_msg,
                        msg->file,
                        msg->line,
                        line_break_character);
        printfCallback_("lhs: %s%s    %s%s", msg->lhs_name, line_break_character, msg->lhs_value, line_break_character);
        printfCallback_("rhs: %s%s    %s%s", msg->rhs_name, line_break_character, msg->rhs_value, line_break_character);

        rmdev_test_finish();
    }
}

void rmdev_test_run_test(rmdev_test_TestSuit* test_suit)
{
    current_running_suit = test_suit;
    ++test_suit_total_count;

    test_suit->body(test_suit);

    if (test_suit->fail_count == 0) {
        ++test_suit_success_count;
    }
    else {
        ++test_suit_fail_count;
    }

    current_running_suit = RMDEV_TEST_NULL;
}

/**
 * rmdev 测试框架 结束测试
 */
static void rmdev_test_finish(void)
{
    if (test_suit_success_count + test_suit_fail_count == test_suit_total_count) {
        printfCallback_("%sTest Finished.%s%s    %d Test suit(s) finished: %d Succeeded, %d Failed.%s",
                        line_break_character,
                        line_break_character,
                        line_break_character,
                        test_suit_total_count,
                        test_suit_success_count,
                        test_suit_fail_count,
                        line_break_character);
    }
    else {
        rmdev_test_error_code = RMDEV_TEST_TEST_SUIT_COUNT_ERROR;

        printfCallback_(
            "rmdev_test_framework Fatal error: Test suit count (%d) does not match success(%d) and fail(%d) "
            "counts!%s",
            test_suit_total_count,
            test_suit_success_count,
            test_suit_fail_count,
            line_break_character);
    }

    END_LOOP();
}

void rmdev_test_framework_main(const char* line_break,
                               const rmdev_test_printfCallback printfCallback,
                               const rmdev_test_delayCallback delayCallback,
                               const rmdev_test_testEntryCallback testEntryCallback)
{
    line_break_character = line_break;

    printfCallback_ = printfCallback;
    delayCallback_ = delayCallback;
    testEntryCallback_ = testEntryCallback;

    if (line_break_character == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_BREAK_CHARACTER;
        END_LOOP();
    }
    if (printfCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_PRINTF_CALLBACK;
        END_LOOP();
    }
    if (delayCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_DELAY_CALLBACK;
        printfCallback_("rmdev_test_framework Fatal error: No delay callback function set!%s", line_break_character);
        END_LOOP();
    }
    if (testEntryCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_TEST_SUIT_CALLBACK;
        printfCallback_("rmdev_test_framework Fatal error: No test suit callback function set!%s",
                        line_break_character);
        END_LOOP();
    }

    testEntryCallback_();

    rmdev_test_finish();
}
