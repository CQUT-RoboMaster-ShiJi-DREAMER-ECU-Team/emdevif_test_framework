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

unsigned char rmdev_test_error_code = RMDEV_TEST_NO_ERROR;           ///< 测试框架错误码

const char* rmdev_test___line_break_character___ = RMDEV_TEST_NULL;  ///< 换行符

rmdev_test_printfCallback rmdev_test___printfCallback___ = RMDEV_TEST_NULL;
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

const rmdev_test_CompareMsg* rmdev_test_checkTure(rmdev_test_CompareMsg* const msg,
                                                  const rmdev_test_CheckType check_type,
                                                  const rmdev_test_bool_t result)
{
    msg->compare_type_msg = "true";
    msg->lhs_name = "expected";
    msg->lhs_value = "true";
    msg->rhs_value = result ? "true" : "false";

    msg->is_passed = result;
    msg->message = rmdev_test___printfCallback___;

    if (check_type == RMDEV_TEST_CHECK_TYPE_EXPECT) {
        rmdev_test_expect(msg->test_suit, msg, result);
    }
    else {
        rmdev_test_assert(msg->test_suit, msg, result);
    }

    return msg;
}

const rmdev_test_CompareMsg* rmdev_test_checkFalse(rmdev_test_CompareMsg* const msg,
                                                   const rmdev_test_CheckType check_type,
                                                   const rmdev_test_bool_t result)
{
    msg->compare_type_msg = "true";
    msg->lhs_name = "expected";
    msg->lhs_value = "false";
    msg->rhs_value = result ? "true" : "false";

    msg->is_passed = !result;
    msg->message = rmdev_test___printfCallback___;

    if (check_type == RMDEV_TEST_CHECK_TYPE_EXPECT) {
        rmdev_test_expect(msg->test_suit, msg, !result);
    }
    else {
        rmdev_test_assert(msg->test_suit, msg, !result);
    }

    return msg;
}

static void rmdev_test_expect(rmdev_test_TestSuit* const test_suit,
                              const rmdev_test_CompareMsg* const msg,
                              const rmdev_test_bool_t result)
{
    ++test_suit->total_count;

    if (result) {
        ++test_suit->success_count;
        rmdev_test___printfCallback___(".");
    }
    else {
        ++test_suit->fail_count;

        rmdev_test___printfCallback___("F%s", rmdev_test___line_break_character___);
        rmdev_test___printfCallback___("Test suit \"%s\" expect %s: \"%s\" failed at ",
                                       test_suit->name,
                                       msg->compare_type_msg,
                                       msg->current_case_name);
        rmdev_test___printfCallback___("%s:%d: %s", msg->file, msg->line, rmdev_test___line_break_character___);
        rmdev_test___printfCallback___("lhs: %s%s    %s%s",
                                       msg->lhs_name,
                                       rmdev_test___line_break_character___,
                                       msg->lhs_value,
                                       rmdev_test___line_break_character___);
        rmdev_test___printfCallback___("rhs: %s%s    %s%s",
                                       msg->rhs_name,
                                       rmdev_test___line_break_character___,
                                       msg->rhs_value,
                                       rmdev_test___line_break_character___);
    }
}

static void rmdev_test_assert(rmdev_test_TestSuit* const test_suit,
                              const rmdev_test_CompareMsg* const msg,
                              const rmdev_test_bool_t result)
{
    ++test_suit->total_count;

    if (result) {
        ++test_suit->success_count;
        rmdev_test___printfCallback___(".");
    }
    else {
        ++test_suit->fail_count;

        rmdev_test___printfCallback___("F%s", rmdev_test___line_break_character___);
        rmdev_test___printfCallback___("Test suit \"%s\" assert %s: \"%s\" failed at ",
                                       test_suit->name,
                                       msg->compare_type_msg,
                                       msg->current_case_name);
        rmdev_test___printfCallback___("%s:%d: %s", msg->file, msg->line, rmdev_test___line_break_character___);
        rmdev_test___printfCallback___("lhs: %s%s    %s%s",
                                       msg->lhs_name,
                                       rmdev_test___line_break_character___,
                                       msg->lhs_value,
                                       rmdev_test___line_break_character___);
        rmdev_test___printfCallback___("rhs: %s%s    %s%s",
                                       msg->rhs_name,
                                       rmdev_test___line_break_character___,
                                       msg->rhs_value,
                                       rmdev_test___line_break_character___);

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
        rmdev_test___printfCallback___("%sTest Finished.%s%s    %d Test suit(s) finished: %d Succeeded, %d Failed.%s",
                                       rmdev_test___line_break_character___,
                                       rmdev_test___line_break_character___,
                                       rmdev_test___line_break_character___,
                                       test_suit_total_count,
                                       test_suit_success_count,
                                       test_suit_fail_count,
                                       rmdev_test___line_break_character___);
    }
    else {
        rmdev_test_error_code = RMDEV_TEST_TEST_SUIT_COUNT_ERROR;

        rmdev_test___printfCallback___(
            "rmdev_test_framework Fatal error: Test suit count (%d) does not match success(%d) and fail(%d) "
            "counts!%s",
            test_suit_total_count,
            test_suit_success_count,
            test_suit_fail_count,
            rmdev_test___line_break_character___);
    }

    END_LOOP();
}

void rmdev_test_framework_main(const char* line_break,
                               const rmdev_test_printfCallback printfCallback,
                               const rmdev_test_delayCallback delayCallback,
                               const rmdev_test_testEntryCallback testEntryCallback)
{
    rmdev_test___line_break_character___ = line_break;

    rmdev_test___printfCallback___ = printfCallback;
    delayCallback_ = delayCallback;
    testEntryCallback_ = testEntryCallback;

    if (rmdev_test___line_break_character___ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_BREAK_CHARACTER;
        END_LOOP();
    }
    if (rmdev_test___printfCallback___ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_PRINTF_CALLBACK;
        END_LOOP();
    }
    if (delayCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_DELAY_CALLBACK;
        rmdev_test___printfCallback___("rmdev_test_framework Fatal error: No delay callback function set!%s",
                                       rmdev_test___line_break_character___);
        END_LOOP();
    }
    if (testEntryCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_TEST_SUIT_CALLBACK;
        rmdev_test___printfCallback___("rmdev_test_framework Fatal error: No test suit callback function set!%s",
                                       rmdev_test___line_break_character___);
        END_LOOP();
    }

    testEntryCallback_();

    rmdev_test_finish();
}
