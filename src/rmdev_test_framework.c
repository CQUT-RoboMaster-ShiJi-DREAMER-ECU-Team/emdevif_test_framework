/**
 * @file rmdev_test_framework.c
 * @author 杜以成
 * @date 2025-06-03
 * @brief rmdev 测试框架
 */

#include "rmdev_test_framework.h"

#include <string.h>

unsigned char rmdev_test_error_code = RMDEV_TEST_NO_ERROR;           ///< 测试框架错误码

const char* rmdev_test___line_break_character___ = RMDEV_TEST_NULL;  ///< 换行符

rmdev_test_printfCallback rmdev_test___printfCallback___ = RMDEV_TEST_NULL;
static rmdev_test_delayCallback delayCallback_ = RMDEV_TEST_NULL;
static rmdev_test_testEntryCallback testEntryCallback_ = RMDEV_TEST_NULL;
static rmdev_test_testFinishCallback testFinishCallback_ = RMDEV_TEST_NULL;
static rmdev_test_errorCallback errorCallback_ = RMDEV_TEST_NULL;

static const rmdev_test_TestSuit* current_running_suit = RMDEV_TEST_NULL;

static int test_suit_total_count = 0;    ///< 测试套件计数
static int test_suit_success_count = 0;  ///< 成功计数
static int test_suit_fail_count = 0;     ///< 失败计数

/**
 * 钩子函数
 * @attention 由框架内部调用
 */
rmdev_test_Hooks rmdev_test___hooks___;

static void rmdev_test_finish(void);
static void rmdev_test_check(const rmdev_test_CompareMsg* msg,
                             rmdev_test_CheckType check_type,
                             rmdev_test_bool_t result);
static void rmdev_test_defaultErrorCallback(rmdev_test_ErrorCode error_code);
static void rmdev_test_deinit(void);

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

/**
 * 检测结果是否为 true
 * @attention 此函数由框架内部调用
 * @param msg 比较信息
 * @param check_type 检测方式（期望或断言）
 * @param result 实际结果
 * @return 比较信息（用于链式调用 message 方法）
 */
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

    rmdev_test_check(msg, check_type, result);

    return msg;
}

/**
 * 检测结果是否为 false
 * @attention 此函数由框架内部调用
 * @param msg 比较信息
 * @param check_type 检测方式（期望或断言）
 * @param result 实际结果
 * @return 比较信息（用于链式调用 message 方法）
 */
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

    rmdev_test_check(msg, check_type, !result);

    return msg;
}

/**
 * 检测判断结果
 * @param msg 比较信息
 * @param check_type
 * @param result 比较结果
 */
static void rmdev_test_check(const rmdev_test_CompareMsg* const msg,
                             const rmdev_test_CheckType check_type,
                             const rmdev_test_bool_t result)
{
    ++msg->test_suit->total_count;

    if (result) {
        ++msg->test_suit->success_count;
        rmdev_test___printfCallback___(".");
    }
    else {
        ++msg->test_suit->fail_count;

        rmdev_test___printfCallback___("F%s", rmdev_test___line_break_character___);
        rmdev_test___printfCallback___("Test suit \"%s\" %s %s: \"%s\" failed at ",
                                       msg->test_suit->name,
                                       ((check_type == RMDEV_TEST_CHECK_TYPE_EXPECT) ? "expect" : "assert"),
                                       msg->compare_type_msg,
                                       msg->current_case_name);
        rmdev_test___printfCallback___("%s:%d:%s", msg->file, msg->line, rmdev_test___line_break_character___);
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

/**
 * 断言失败后的入口函数
 * @attention 此函数由框架内部调用
 */
void rmdev_test_assertFailEntry(void)
{
    rmdev_test_finish();
}

/**
 * 执行测试套件
 * @attention 此函数由框架内部调用
 * @param test_suit 测试套件
 */
void rmdev_test_run_test_suit(rmdev_test_TestSuit* test_suit)
{
    current_running_suit = test_suit;
    ++test_suit_total_count;

    RMDEV_TEST__RUN_HOOK(rmdev_test___hooks___.testSuitBeginHook, test_suit);

    test_suit->body(test_suit);

    RMDEV_TEST__RUN_HOOK(rmdev_test___hooks___.testSuitEndHook, test_suit);

    if (test_suit->fail_count == 0) {
        ++test_suit_success_count;
    }
    else {
        ++test_suit_fail_count;
    }

    if (current_running_suit->total_count != current_running_suit->success_count + current_running_suit->fail_count) {
        rmdev_test_error_code = RMDEV_TEST_TEST_SUIT_COUNT_ERROR;

        rmdev_test___printfCallback___(
            "rmdev_test_framework Fatal error: Test suit \"%s\" case count(%d) does not match success(%d) and fail(%d) "
            "counts!%s",
            current_running_suit->name,
            current_running_suit->total_count,
            current_running_suit->success_count,
            current_running_suit->fail_count,
            rmdev_test___line_break_character___);

        errorCallback_(rmdev_test_error_code);
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
            "rmdev_test_framework Fatal error: Test suit count(%d) does not match success(%d) and fail(%d) "
            "counts!%s",
            test_suit_total_count,
            test_suit_success_count,
            test_suit_fail_count,
            rmdev_test___line_break_character___);

        errorCallback_(rmdev_test_error_code);
    }

    RMDEV_TEST__RUN_HOOK(rmdev_test___hooks___.testEndHook,
                         test_suit_total_count,
                         test_suit_success_count,
                         test_suit_fail_count);

    if (testFinishCallback_ == RMDEV_TEST_NULL) {
        END_LOOP();
    }
    else {
        testFinishCallback_();
    }
}

void rmdev_test_framework_main(const char* line_break,
                               const rmdev_test_Callbacks* const callback,
                               const rmdev_test_Hooks* const user_hooks)
{
    rmdev_test_deinit();

    rmdev_test___line_break_character___ = line_break;

    rmdev_test___printfCallback___ = callback->printfCallback;
    delayCallback_ = callback->delayCallback;
    testEntryCallback_ = callback->testEntryCallback;
    testFinishCallback_ = callback->testFinishCallback;
    errorCallback_ = callback->errorCallback;

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
        rmdev_test___printfCallback___("rmdev_test_framework Init error: No delay callback function set!%s",
                                       rmdev_test___line_break_character___);
        END_LOOP();
    }
    if (testEntryCallback_ == RMDEV_TEST_NULL) {
        rmdev_test_error_code = RMDEV_TEST_NO_TEST_ENTRY_CALLBACK;
        rmdev_test___printfCallback___("rmdev_test_framework Init error: No test entry callback function set!%s",
                                       rmdev_test___line_break_character___);
        END_LOOP();
    }
    if (errorCallback_ == RMDEV_TEST_NULL) {
        errorCallback_ = rmdev_test_defaultErrorCallback;
    }

    if (user_hooks == RMDEV_TEST_NULL) {
        memset(&rmdev_test___hooks___, 0, sizeof(rmdev_test_Hooks));
    }
    else {
        rmdev_test___hooks___ = *user_hooks;
    }

    RMDEV_TEST__RUN_HOOK(rmdev_test___hooks___.testBeginHook, );

    testEntryCallback_();

    rmdev_test_finish();
}

/**
 * 默认的错误处理回调函数
 * @param error_code 错误码
 */
static void rmdev_test_defaultErrorCallback(const rmdev_test_ErrorCode error_code)
{
    (void)error_code;

    END_LOOP();
}

/**
 * 重置测试框架
 */
static void rmdev_test_deinit(void)
{
    rmdev_test_error_code = RMDEV_TEST_NO_ERROR;

    rmdev_test___line_break_character___ = RMDEV_TEST_NULL;

    rmdev_test___printfCallback___ = RMDEV_TEST_NULL;
    delayCallback_ = RMDEV_TEST_NULL;
    testEntryCallback_ = RMDEV_TEST_NULL;
    testFinishCallback_ = RMDEV_TEST_NULL;
    errorCallback_ = RMDEV_TEST_NULL;

    current_running_suit = RMDEV_TEST_NULL;

    test_suit_total_count = 0;
    test_suit_success_count = 0;
    test_suit_fail_count = 0;
}
