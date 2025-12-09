/**
 * @file emdevif_test_framework.c
 * @brief emdevif 测试框架
 */

#include "emdevif_test_framework/core.h"

#include <string.h>
#include <stdio.h>
#include <math.h>

emdevif_test_ErrorCode emdevif_test_error_code = EMDEVIF_TEST_NO_ERROR;  ///< 测试框架错误码

const char* emdevif_test___line_break_character___ = EMDEVIF_TEST_NULL;  ///< 换行符

emdevif_test_printfCallback emdevif_test___printfCallback___ = EMDEVIF_TEST_NULL;
static emdevif_test_testEntryCallback testEntryCallback_ = EMDEVIF_TEST_NULL;
static emdevif_test_testFinishCallback testFinishCallback_ = EMDEVIF_TEST_NULL;
static emdevif_test_errorCallback errorCallback_ = EMDEVIF_TEST_NULL;

static const emdevif_test_TestSuit* current_running_suit = EMDEVIF_TEST_NULL;

static int test_suit_total_count = 0;    ///< 测试套件计数
static int test_suit_success_count = 0;  ///< 成功计数
static int test_suit_fail_count = 0;     ///< 失败计数

#ifndef EMDEVIF_TEST_VALUE_BUFFER_SIZE
#define EMDEVIF_TEST_VALUE_BUFFER_SIZE 64
#endif

static char lhs_buffer[EMDEVIF_TEST_VALUE_BUFFER_SIZE], rhs_buffer[EMDEVIF_TEST_VALUE_BUFFER_SIZE];

/**
 * 钩子函数
 * @attention 由框架内部调用
 */
emdevif_test_Hooks emdevif_test___hooks___;

emdevif_test_TestSuit emdevif_current_test_suit_;               ///< 当前运行的测试套件
emdevif_test_CompareMsg emdevif_current_test_compare_message_;  ///< 当前运行的测试的比较信息

#ifndef EMDEVIF_TEST_FLOAT_EQUAL_ERROR
#define EMDEVIF_TEST_FLOAT_EQUAL_ERROR 0.0001
#endif

static emdevif_test_bool_t floatPointEqual(double lhs, double rhs);
static void setCompareName(emdevif_test_CompareMsg* msg, emdevif_test_CompareType compare_type);
static void emdevif_test_finish(void);
static void printCheckResult(const emdevif_test_CompareMsg* msg, emdevif_test_CheckType check_type);
static void emdevif_test_defaultErrorCallback(emdevif_test_ErrorCode error_code);
static void emdevif_test_deinit(void);

/// 结束的死循环
#define END_LOOP() \
    do {           \
    } while (EMDEVIF_TEST_TRUE)

#define DECL_COMPARE(Type) emdevif_test_bool_t compare_##Type(Type lhs, Type rhs, emdevif_test_CompareType compare_type)

#define DEF_COMPARE(Type)                                                                                           \
    emdevif_test_bool_t compare_##Type(const Type lhs, const Type rhs, const emdevif_test_CompareType compare_type) \
    {                                                                                                               \
        switch (compare_type) {                                                                                     \
        case EMDEVIF_TEST_COMPARE_EQUAL:                                                                            \
            return (lhs == rhs);                                                                                    \
        case EMDEVIF_TEST_COMPARE_NOT_EQUAL:                                                                        \
            return (lhs != rhs);                                                                                    \
        case EMDEVIF_TEST_COMPARE_GREATER_THAN:                                                                     \
            return (lhs > rhs);                                                                                     \
        case EMDEVIF_TEST_COMPARE_LESS_THAN:                                                                        \
            return (lhs < rhs);                                                                                     \
        case EMDEVIF_TEST_COMPARE_GREATER_EQUAL:                                                                    \
            return (lhs >= rhs);                                                                                    \
        case EMDEVIF_TEST_COMPARE_LESS_EQUAL:                                                                       \
            return (lhs <= rhs);                                                                                    \
                                                                                                                    \
        default:                                                                                                    \
            return EMDEVIF_TEST_FALSE;                                                                              \
        }                                                                                                           \
    }

#define CALL_COMPARE(Type) compare_##Type

typedef unsigned int emdevif_test_uint_t;

static DECL_COMPARE(int);
static DECL_COMPARE(emdevif_test_uint_t);
static DECL_COMPARE(double);

void emdevif_test_TestFixture_Constructor(void* const this_,
                                          void (*setUp)(emdevif_test_TestFixture* this_),
                                          void (*tearDown)(emdevif_test_TestFixture* this_))
{
    emdevif_test_TestFixture* const self = (emdevif_test_TestFixture*)this_;

    if (self != EMDEVIF_TEST_NULL) {
        self->setUp = setUp;
        self->tearDown = tearDown;
    }
}

/**
 * 设置比较的名称
 * @param msg 比较的信息
 * @param compare_type 比较的类型
 */
static void setCompareName(emdevif_test_CompareMsg* const msg, const emdevif_test_CompareType compare_type)
{
    switch (compare_type) {
    case EMDEVIF_TEST_COMPARE_EQUAL:
        msg->compare_type_name = "==";
        break;
    case EMDEVIF_TEST_COMPARE_NOT_EQUAL:
        msg->compare_type_name = "!=";
        break;
    case EMDEVIF_TEST_COMPARE_GREATER_THAN:
        msg->compare_type_name = ">";
        break;
    case EMDEVIF_TEST_COMPARE_LESS_THAN:
        msg->compare_type_name = "<";
        break;
    case EMDEVIF_TEST_COMPARE_GREATER_EQUAL:
        msg->compare_type_name = ">=";
        break;
    case EMDEVIF_TEST_COMPARE_LESS_EQUAL:
        msg->compare_type_name = "<=";
        break;

    default:
        break;
    }
}

/**
 * 字符串相等
 * @attention 此函数由框架内部调用
 * @param msg 比较信息
 * @param check_type 检查类型
 * @param lhs 左侧参数
 * @param rhs 右侧参数
 * @return 比较信息（用于链式调用 MESSAGE 宏）
 */
const emdevif_test_CompareMsg* emdevif_test_strEqual(emdevif_test_CompareMsg* const msg,
                                                     const emdevif_test_CheckType check_type,
                                                     const char* const lhs,
                                                     const char* const rhs)
{
    msg->lhs_value = lhs;
    msg->rhs_value = rhs;

    setCompareName(msg, EMDEVIF_TEST_COMPARE_EQUAL);

    msg->is_passed = (strcmp(lhs, rhs) == 0);

    printCheckResult(msg, check_type);

    return msg;
}

/**
 * 整型比较
 * @attention 此函数由框架内部调用
 * @param msg 比较信息
 * @param check_type 检查类型
 * @param compare_type 比较类型
 * @param lhs 左侧参数
 * @param rhs 右侧参数
 * @return 比较信息（用于链式调用 MESSAGE 宏）
 */
const emdevif_test_CompareMsg* emdevif_test_intCompare(emdevif_test_CompareMsg* const msg,
                                                       const emdevif_test_CheckType check_type,
                                                       const emdevif_test_CompareType compare_type,
                                                       const int lhs,
                                                       const int rhs)
{
    sprintf(lhs_buffer, "%d (%#x)", lhs, lhs);
    sprintf(rhs_buffer, "%d (%#x)", rhs, rhs);
    msg->lhs_value = lhs_buffer;
    msg->rhs_value = rhs_buffer;

    setCompareName(msg, compare_type);

    msg->is_passed = CALL_COMPARE(int)(lhs, rhs, compare_type);

    printCheckResult(msg, check_type);

    return msg;
}

/**
 * 无符号整型比较
 * @attention 此函数由框架内部调用
 * @param msg 比较信息
 * @param check_type 检查类型
 * @param compare_type 比较类型
 * @param lhs 左侧参数
 * @param rhs 右侧参数
 * @return 比较信息（用于链式调用 MESSAGE 宏）
 */
const emdevif_test_CompareMsg* emdevif_test_uintCompare(emdevif_test_CompareMsg* const msg,
                                                        const emdevif_test_CheckType check_type,
                                                        const emdevif_test_CompareType compare_type,
                                                        const unsigned int lhs,
                                                        const unsigned int rhs)
{
    sprintf(lhs_buffer, "%u (%#x)", lhs, lhs);
    sprintf(rhs_buffer, "%u (%#x)", rhs, rhs);
    msg->lhs_value = lhs_buffer;
    msg->rhs_value = rhs_buffer;

    setCompareName(msg, compare_type);

    msg->is_passed = CALL_COMPARE(emdevif_test_uint_t)(lhs, rhs, compare_type);

    printCheckResult(msg, check_type);

    return msg;
}

/**
 * 判断浮点数是否相等（二者之差的绝对值小于 EMDEVIF_TEST_FLOAT_EQUAL_ERROR 时，认为相等）
 * @param lhs 左侧参数
 * @param rhs 右侧参数
 * @return 是否相等
 */
static emdevif_test_bool_t floatPointEqual(const double lhs, const double rhs)
{
    return (fabs(lhs - rhs) <= EMDEVIF_TEST_FLOAT_EQUAL_ERROR);
}

/**
 * 浮点类型比较（二者之差的绝对值小于 EMDEVIF_TEST_FLOAT_EQUAL_ERROR 时，认为相等）
 * @attention 此函数由框架内部调用
 * @param msg 比较信息
 * @param check_type 检查类型
 * @param compare_type 比较类型
 * @param lhs 左侧参数
 * @param rhs 右侧参数
 * @return 比较信息（用于链式调用 MESSAGE 宏）
 */
const emdevif_test_CompareMsg* emdevif_test_floatPointCompare(emdevif_test_CompareMsg* const msg,
                                                              const emdevif_test_CheckType check_type,
                                                              const emdevif_test_CompareType compare_type,
                                                              const double lhs,
                                                              const double rhs)
{
    sprintf(lhs_buffer, "%lf", lhs);
    sprintf(rhs_buffer, "%lf", rhs);
    msg->lhs_value = lhs_buffer;
    msg->rhs_value = rhs_buffer;

    setCompareName(msg, compare_type);

    switch (compare_type) {
    case EMDEVIF_TEST_COMPARE_EQUAL:
        msg->is_passed = floatPointEqual(lhs, rhs);
        break;

    case EMDEVIF_TEST_COMPARE_NOT_EQUAL:
        msg->is_passed = !floatPointEqual(lhs, rhs);
        break;

    default:
        msg->is_passed = CALL_COMPARE(double)(lhs, rhs, compare_type);
        break;
    }

    printCheckResult(msg, check_type);

    return msg;
}

/**
 * 检测结果是否为 true
 * @attention 此函数由框架内部调用
 * @param msg 比较信息
 * @param check_type 检测方式（期望或断言）
 * @param result 实际结果
 * @return 比较信息（用于链式调用 MESSAGE 宏）
 */
const emdevif_test_CompareMsg* emdevif_test_checkTure(emdevif_test_CompareMsg* const msg,
                                                      const emdevif_test_CheckType check_type,
                                                      const emdevif_test_bool_t result)
{
    msg->compare_type_name = "true";
    msg->lhs_name = "expected";
    msg->lhs_value = "true";
    msg->rhs_value = result ? "true" : "false";

    msg->is_passed = result;

    printCheckResult(msg, check_type);

    return msg;
}

/**
 * 检测结果是否为 false
 * @attention 此函数由框架内部调用
 * @param msg 比较信息
 * @param check_type 检测方式（期望或断言）
 * @param result 实际结果
 * @return 比较信息（用于链式调用 MESSAGE 宏）
 */
const emdevif_test_CompareMsg* emdevif_test_checkFalse(emdevif_test_CompareMsg* const msg,
                                                       const emdevif_test_CheckType check_type,
                                                       const emdevif_test_bool_t result)
{
    msg->compare_type_name = "true";
    msg->lhs_name = "expected";
    msg->lhs_value = "false";
    msg->rhs_value = result ? "true" : "false";

    msg->is_passed = !result;

    printCheckResult(msg, check_type);

    return msg;
}

/**
 * 输出检查结果
 * @param msg 比较信息
 * @param check_type 检测方式（期望或断言）
 */
static void printCheckResult(const emdevif_test_CompareMsg* const msg, const emdevif_test_CheckType check_type)
{
    ++msg->test_suit->total_count;

    if (msg->is_passed) {
        ++msg->test_suit->success_count;
        emdevif_test___printfCallback___(".");
    }
    else {
        ++msg->test_suit->fail_count;

        emdevif_test___printfCallback___("F%s", emdevif_test___line_break_character___);
        emdevif_test___printfCallback___("Test suit \"%s\" %s \"%s\": Case \"%s\" failed at ",
                                         msg->test_suit->name,
                                         ((check_type == EMDEVIF_TEST_CHECK_TYPE_EXPECT) ? "expect" : "assert"),
                                         msg->compare_type_name,
                                         msg->current_case_name);
        emdevif_test___printfCallback___("%s:%d:%s", msg->file, msg->line, emdevif_test___line_break_character___);
        emdevif_test___printfCallback___("lhs: %s%s    %s%s",
                                         msg->lhs_name,
                                         emdevif_test___line_break_character___,
                                         msg->lhs_value,
                                         emdevif_test___line_break_character___);
        emdevif_test___printfCallback___("rhs: %s%s    %s%s",
                                         msg->rhs_name,
                                         emdevif_test___line_break_character___,
                                         msg->rhs_value,
                                         emdevif_test___line_break_character___);
    }
}

/**
 * 断言失败后的入口函数
 * @attention 此函数由框架内部调用
 */
void emdevif_test_assertFailEntry(void)
{
    ++test_suit_fail_count;
    emdevif_test_finish();
}

/**
 * 执行测试套件
 * @attention 此函数由框架内部调用
 * @param test_suit 测试套件
 */
void emdevif_test_run_test_suit(emdevif_test_TestSuit* test_suit)
{
    current_running_suit = test_suit;
    ++test_suit_total_count;

    EMDEVIF_TEST__RUN_HOOK(emdevif_test___hooks___.testSuitBeginHook, test_suit);

    emdevif_test___printfCallback___("* Running suit \"%s\" ", test_suit->name);

    test_suit->body(test_suit);

    emdevif_test___printfCallback___("%s", emdevif_test___line_break_character___);

    EMDEVIF_TEST__RUN_HOOK(emdevif_test___hooks___.testSuitEndHook, test_suit);

    if (test_suit->fail_count == 0) {
        ++test_suit_success_count;
    }
    else {
        ++test_suit_fail_count;
    }

    if (current_running_suit->total_count != current_running_suit->success_count + current_running_suit->fail_count) {
        emdevif_test_error_code = EMDEVIF_TEST_TEST_SUIT_COUNT_ERROR;

        emdevif_test___printfCallback___(
            "emdevif_test_framework Fatal error: Test suit \"%s\" case count(%d) does not match success(%d) and "
            "fail(%d) "
            "counts!%s",
            current_running_suit->name,
            current_running_suit->total_count,
            current_running_suit->success_count,
            current_running_suit->fail_count,
            emdevif_test___line_break_character___);

        errorCallback_(emdevif_test_error_code);
    }

    current_running_suit = EMDEVIF_TEST_NULL;
}

/**
 * emdevif 测试框架 结束测试
 */
static void emdevif_test_finish(void)
{
    if (test_suit_success_count + test_suit_fail_count == test_suit_total_count) {
        emdevif_test___printfCallback___("%sTest Finished.%s%s    %d Test suit(s) finished: %d Succeeded, %d Failed.%s",
                                         emdevif_test___line_break_character___,
                                         emdevif_test___line_break_character___,
                                         emdevif_test___line_break_character___,
                                         test_suit_total_count,
                                         test_suit_success_count,
                                         test_suit_fail_count,
                                         emdevif_test___line_break_character___);
    }
    else {
        emdevif_test_error_code = EMDEVIF_TEST_TEST_SUIT_COUNT_ERROR;

        emdevif_test___printfCallback___(
            "emdevif_test_framework Fatal error: Test suit count(%d) does not match success(%d) and fail(%d) "
            "counts!%s",
            test_suit_total_count,
            test_suit_success_count,
            test_suit_fail_count,
            emdevif_test___line_break_character___);

        errorCallback_(emdevif_test_error_code);
    }

    EMDEVIF_TEST__RUN_HOOK(emdevif_test___hooks___.testEndHook,
                           test_suit_total_count,
                           test_suit_success_count,
                           test_suit_fail_count);

    if (testFinishCallback_ == EMDEVIF_TEST_NULL) {
        END_LOOP();
    }
    else {
        if (emdevif_test_error_code == EMDEVIF_TEST_NO_ERROR && test_suit_fail_count == 0) {
            testFinishCallback_(EMDEVIF_TEST_ALL_PASSED);
        }
        else {
            testFinishCallback_(EMDEVIF_TEST_EXIST_FAIL);
        }
    }
}

void emdevif_test_framework_main(const char* line_break,
                                 const emdevif_test_Callbacks* const callback,
                                 const emdevif_test_Hooks* const user_hooks)
{
    emdevif_test_deinit();

    emdevif_test___line_break_character___ = line_break;

    emdevif_test___printfCallback___ = callback->printfCallback;
    testEntryCallback_ = callback->testEntryCallback;
    testFinishCallback_ = callback->testFinishCallback;
    errorCallback_ = callback->errorCallback;

    if (errorCallback_ == EMDEVIF_TEST_NULL) {
        errorCallback_ = emdevif_test_defaultErrorCallback;
    }

    if (emdevif_test___line_break_character___ == EMDEVIF_TEST_NULL) {
        emdevif_test_error_code = EMDEVIF_TEST_NO_BREAK_CHARACTER;
        errorCallback_(emdevif_test_error_code);
    }
    if (emdevif_test___printfCallback___ == EMDEVIF_TEST_NULL) {
        emdevif_test_error_code = EMDEVIF_TEST_NO_PRINTF_CALLBACK;
        errorCallback_(emdevif_test_error_code);
    }
    if (testEntryCallback_ == EMDEVIF_TEST_NULL) {
        emdevif_test_error_code = EMDEVIF_TEST_NO_TEST_ENTRY_CALLBACK;
        emdevif_test___printfCallback___("emdevif_test_framework Init error: No test entry callback function set!%s",
                                         emdevif_test___line_break_character___);
        errorCallback_(emdevif_test_error_code);
    }

    if (user_hooks == EMDEVIF_TEST_NULL) {
        memset(&emdevif_test___hooks___, 0, sizeof(emdevif_test_Hooks));
    }
    else {
        emdevif_test___hooks___ = *user_hooks;
    }

    EMDEVIF_TEST__RUN_HOOK(emdevif_test___hooks___.testBeginHook, );

    testEntryCallback_();

    emdevif_test_finish();
}

/**
 * 默认的错误处理回调函数
 * @param error_code 错误码
 */
static void emdevif_test_defaultErrorCallback(const emdevif_test_ErrorCode error_code)
{
    (void)error_code;

    END_LOOP();
}

/**
 * 重置测试框架
 */
static void emdevif_test_deinit(void)
{
    emdevif_test_error_code = EMDEVIF_TEST_NO_ERROR;

    emdevif_test___line_break_character___ = EMDEVIF_TEST_NULL;

    emdevif_test___printfCallback___ = EMDEVIF_TEST_NULL;
    testEntryCallback_ = EMDEVIF_TEST_NULL;
    testFinishCallback_ = EMDEVIF_TEST_NULL;
    errorCallback_ = EMDEVIF_TEST_NULL;

    current_running_suit = EMDEVIF_TEST_NULL;

    test_suit_total_count = 0;
    test_suit_success_count = 0;
    test_suit_fail_count = 0;
}

/* clang-format off */

static DEF_COMPARE(int)
static DEF_COMPARE(emdevif_test_uint_t)
static DEF_COMPARE(double)

    /* clang-format on */
